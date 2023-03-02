module;
export module autl.type_traits.commonreference;

import autl.type_traits.commontype;
import autl.type_traits.convertible;
import autl.type_traits.reference;
import autl.type_traits.removecvref;
import autl.type_traits.constvolatile;
import autl.utility.declval;

export namespace autl
{
  template<typename, typename, template <typename> typename, template <typename> typename>
  struct BasicCommonReference {};
}

namespace autl
{
  // Largely based on the libcxx implementation since that one actually came with (some) implementation details!

  // From cppreference...
  // When given reference types, CommonReference attempts to find a reference type to which the supplied reference types can all be bound, but may return a non-reference type if it cannot find such a type
  // - if sizeof...(T) is 0, there is no member type
  // - if sizeof...(T) is 1, (i.e. T... contains only T0), the member Type is T0
  // - if sizeof...(T) is 2, (i.e. T... contains T1 and T2)
  //    - If T1 and T2 are both reference types and the simple common reference type S of T1 and T2 exists, then the member Type is S
  //    - Otherwise, if BasicCommonReference<RemoveCVRef_t<T1>, RemoveCVRef_t<T2>, XRef<T1>::template Apply, XRef<T2>::template Apply>::Type exists, then the member Type is that type
  //    - Otherwise, if decltype(false ? val<T1>() : val<T2>()) is a valid type, where val is a function template template<typename T> T val(), then the member Type is that type
  //    - Otherwise, if CommonType_t<T1, T2> is a valid type, then member Type is that type
  //    - Otherwise, there is no member type
  // - if sizeof...(T) is greater than 2 then if CommonReference_t<T1, T2> exists, then the member type denotes CommonReference_t<CommonReference<T1, T2>, Rest...> if such a type exists. In all other cases, there is no member type
  // 
  // The simple common reference type of two reference types T1 and T2 is defined as follows:
  // - If T1 is cv1 X& and T2 is cv2 Y& (i.e. both are lvalue reference types):
  //    - Their simple common reference type is:
  //      decltype(false ? Declval<cv12 X&>() : Declval<cv12 Y&>()), where cv12 is the union of cv1 and cv2, if that type exists and is a reference type
  // - If T1 and T2 ar both rvalue reference types:
  //    - if the simple common reference type of T1& and T2& exists (determined according to the previous bullet) 
  //      then let C denote that type's corresponding rvalue reference type. 
  //      If IsConvertible<T1, C> and IsConvertible<T2, C> are both true, then the simple common reference type of T1 and T2 is C
  // - Otherwise, one of the two types must be an lvalue reference type A& and the other must be an rvalue reference type B&&
  //    - Let D denote the simple common reference type of A& and B const&, if any. 
  //      If D exists and IsConvertible<B&&, D> is true, then the simple common reference type is D
  // - Otherwise, there is no simple common reference type

  // Honestly, no idea what this does or why it's called this. 
  // This one is a lot scarier than the one in CommonType
  template<typename X, typename Y> using CondRes = decltype(false ? Declval<X(&)()>()() : Declval<Y(&)()>()());

  // XREF(A) denotes a unary alias template T such that T<U> denotes the same type as U
  // with the additon of A's cv and ref qualifiers
  // XRef is short-hand for cross-ref, hence the transference of qualifiers
  // In other words, we copy the const, volatile, and reference qualifiers from U to T
  template<typename T>
  struct XRef
  {
    template<typename U>
    using Apply = TransferCVRef_t<T, U>;
  };

  template<typename T1, typename T2>
  using BasicCommonReference_t =
    typename BasicCommonReference<RemoveCVRef_t<T1>, RemoveCVRef_t<T2>, XRef<T1>::template Apply, XRef<T2>::template Apply>::Type;

  // Internal helper CommonRef signature
  template<typename A, typename B, typename X=RemoveReference_t<A>, typename Y=RemoveReference_t<B>>
  struct CommonRef;
  // ::Type helper for CommonRef
  template<typename X, typename Y> 
  using CommonRef_t = typename CommonRef<X, Y>::Type;

  // Alias wherein we copy the const-volatile reference qualifiers from X to Y and vice versa
  template<typename X, typename Y>
  using CVCondRes = CondRes<TransferCVRef_t<X, Y>&, TransferCVRef_t<Y, X>&>;

  // When A and B are both lvalue reference types, CommonRef is CondRes(CopyCV(X,Y)&, CopyCV(Y,X)&) 
  // if that type exists and is a reference type
  template<typename A, typename B, typename X, typename Y>
    requires requires { typename CVCondRes<X, Y>; } && IsReference_v<CVCondRes<X, Y>>
  struct CommonRef<A&, B&, X, Y>
  {
    using Type = CVCondRes<X, Y>;
  };

  // Otherwise, let C be RemoveReference_t<CommonRef(X&, Y&)>&&
  template<typename X, typename Y>
  using CommonRefC = RemoveReference_t<CommonRef_t<X&, Y&>>&&;

  // If A and B are both rvalue reference types, C is well-formed,
  // and IsConvertible_v<A, C> && IsConvertible_v<B, C> is true, then CommonRef(A, B) is C
  template<typename A, typename B, typename X, typename Y>
    requires 
       requires { typename CommonRefC<X, Y>; } 
    && IsConvertible_v<A&&, CommonRefC<X, Y>> 
    && IsConvertible_v<B&&, CommonRefC<X, Y>>
  struct CommonRef<A&&, B&&, X, Y>
  {
      using Type = CommonRefC<X, Y>;
  };

  // Other, let D be CommonRef(const X&, Y&)
  template<typename X, typename Y>
  using CommonRefD = CommonRef_t<const X&, Y&>;

  // If A is an rvalue reference and B is an lvalue reference 
  // and D is well-formed
  // and IsConvertible_v<A,D> is true, then CommonRef(A, B) is D
  template<typename A, typename B, typename X, typename Y>
    requires requires { typename CommonRefD<X, Y>; } && IsConvertible_v<A&&, CommonRefD<X, Y>>
  struct CommonRef<A&&, B&, X, Y>
  {
    using Type = CommonRefD<X, Y>;
  };

  // Otherwise if A is an lvalue reference and B is an rvalue reference then CommonRef(A, B) is CommonRef(B, A)
  template<typename A, typename B, typename X, typename Y>
  struct CommonRef<A&, B&&, X, Y> : CommonRef<B&&, A&> {};

  // Otherwise, CommonRef(A, B) is ill-formed
  template<typename A, typename B, typename X, typename Y> struct CommonRef {};

  // Bullet 3 (sizeof...(T) == 2) helpers
  template<typename T1, typename T2> struct CommonRefSubBullet3;
  template<typename T1, typename T2> struct CommonRefSubBullet2 : CommonRefSubBullet3<T1, T2> {};
  template<typename T1, typename T2> struct CommonRefSubBullet1 : CommonRefSubBullet2<T1, T2> {};

  template<typename T1, typename T2>
    requires IsReference_v<T1> && IsReference_v<T2> && requires { typename CommonRef_t<T1, T2>; }
  struct CommonRefSubBullet1<T1, T2>
  {
    using Type = CommonRef_t<T1, T2>;
  };

  template<typename T1, typename T2>
    requires requires { typename BasicCommonReference_t<T1, T2>; }
  struct CommonRefSubBullet2<T1, T2>
  {
    using Type = BasicCommonReference_t<T1, T2>;
  };

  template<typename T1, typename T2>
    requires requires { typename CondRes<T1, T2>; }
  struct CommonRefSubBullet3<T1, T2>
  {
    using Type = CondRes<T1, T2>;
  };

  // Sub-bullet 4, use CommonType
  template<typename T1, typename T2> struct CommonRefSubBullet3 : CommonType<T1, T2> {};
}



export namespace autl
{
  /*
  * Determine the common reference type of the given types T...
  * Finds the type to which all types in T... can be converted or bound
  * If such a type exists, expose a member Type as that that, otherwise there is no member type
  * Behaviour is undefined is any types in T... are incomplete other than void
  */
  template<typename...> struct CommonReference;
  // sizeof...(T) == 0
  template<> struct CommonReference<> {};
  // sizeof...(T) == 1
  template<typename T> struct CommonReference<T>
  {
    using Type = T;
  };
  // sizeof...(T) == 2
  template<typename T1, typename T2> struct CommonReference<T1, T2> : CommonRefSubBullet1<T1, T2> {};
  // sizeof...(T) > 2
  template<typename A, typename B, typename C, typename... Rest>
    requires requires { typename CommonReference<A, B>::Type; }
  struct CommonReference<A, B, C, Rest...> : CommonReference<typename CommonReference<A, B>::Type, C, Rest...> {};
  // Bullet 5 - No common reference, no member Type
  template<typename...> struct CommonReference {};

  /*
  * Helper to access ::Type of CommonReference
  */
  template<typename... Ts>
  using CommonReference_t = typename CommonReference<Ts...>::Type;
}

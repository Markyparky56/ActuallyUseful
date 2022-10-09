module;
export module autl.type_traits.pointer;

import autl.type_traits.core;
import autl.type_traits.reference;
import autl.type_traits.integralconstant;
import autl.type_traits.constvolatile;
import autl.type_traits.isfunction;
import autl.type_traits.isvoid;

namespace autl
{
  // pointer type cannot be formed
  template<typename T, typename=void>
  struct AddPointerHelper
  {
    using Type = T;
  };

  // pointer type can be formed
  template<typename T>
  struct AddPointerHelper<T, Void_t<RemoveReference_t<T>*>>
  {
    using Type = RemoveReference_t<T>*;
  };

  template<typename T> struct IsMemberPointerHelper : FalseType {};
  template<typename T, typename U> struct IsMemberPointerHelper<T U::*> : TrueType {};

  template<typename T> struct IsMemberFunctionPointerHelper : FalseType {};
  template<typename T, typename U> struct IsMemberFunctionPointerHelper<T U::*> : IsFunction<T> {};
}

export namespace autl
{
  /*
  * Determine if given type is a pointer to an object or function (but not a pointer to a member/member function)
  * CV-qualifiers included
  * Refer to IsMember* variants for member pointer types
  */
  template<typename T> struct IsPointer : FalseType {};
  template<typename T> struct IsPointer<T*> : TrueType {};
  template<typename T> struct IsPointer<T* const> : TrueType {};
  template<typename T> struct IsPointer<T* volatile> : TrueType {};
  template<typename T> struct IsPointer<T* const volatile> : TrueType {};

  /*
  * Helper to access ::Value from IsPointer
  */
  template<typename T> inline constexpr bool IsPointer_v = IsPointer<T>::Value;

  /*
  * Determine if given type is a pointer to a non-static member object or function
  */
  template<typename T> struct IsMemberPointer : IsMemberPointerHelper<RemoveCV_t<T>> {};

  /*
  * Helper to access ::Value from IsMemberPointer
  */
  template<typename T> inline constexpr bool IsMemberPointer_v = IsMemberPointer<T>::Value;

  /*
  * Determine if given type is a pointer to a non-static member function
  */
  template<typename T> struct IsMemberFunctionPointer : IsMemberFunctionPointerHelper<RemoveCV_t<T>> {};

  /*
  * Helper to access ::Value from IsMemberFunctionPointer  
  */
  template<typename T> inline constexpr bool IsMemberFunctionPointer_v = IsMemberFunctionPointer<T>::Value;

  /*
  * Determine if given type is a pointer to a non-static member object
  */
  template<typename T> struct IsMemberObjectPointer : BoolConstant<IsMemberPointer_v<T> && !IsMemberFunctionPointer_v<T>> {};

  /*
  * Helper to access ::Value from IsMemberObjectPointer
  */
  template<typename T> inline constexpr bool IsMemberObjectPointer_v = IsMemberObjectPointer<T>::Value;

  /*
  * If given type is a reference type, provide Type as a pointer to the referred type
  * If given type is an object type, a function type that is not cv- or ref-qualified, or a void type, provides T*
  * If unable to perform above, Type will be T
  */
  template<typename T> struct AddPointer { using Type = AddPointerHelper<T>::Type; };

  /*
  * Helper to access ::Type of AddPointer 
  */
  template<typename T> using AddPointer_t = typename AddPointer<T>::Type;

  /*
  * Remove one level of pointer from a type
  */
  template<typename T> struct RemovePointer { using Type = T; };
  template<typename T> struct RemovePointer<T*> { using Type = T; };
  template<typename T> struct RemovePointer<T* const> { using Type = T; };
  template<typename T> struct RemovePointer<T* volatile> { using Type = T; };
  template<typename T> struct RemovePointer<T* const volatile> { using Type = T; };

  /*
  * Helper to access ::Type of RemovePointer
  */
  template<typename T> using RemovePointer_t = typename RemovePointer<T>::Type;
}
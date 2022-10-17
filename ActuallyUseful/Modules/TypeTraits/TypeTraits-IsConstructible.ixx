module;
export module autl.type_traits.isconstructible;

import autl.type_traits.integralconstant;
import autl.type_traits.reference;
import autl.type_traits.isvoid;

namespace autl
{
  // Helper to IsImplicitlyDefaultConstructible
  template<typename T> void ImplicitlyDefaultConstructibleHelper(const T&);
}

export namespace autl
{
  /*
  * True if T is an object or reference type and provided args form a well-formed variable definition (T obj(Declval<Args>()...)  * 
  */
  template<typename T, typename... Args>
  struct IsConstructible : BoolConstant<__is_constructible(T, Args...)> 
  {
    // Both MSVC & Clang use builtins for this
  };

  /*
  * Helper to access ::Value of IsConstructible
  */
  template<typename T, typename... Args> 
  inline constexpr bool IsConstructible_v = IsConstructible<T, Args...>::Value;

  /*
  * True if IsConstructible, but the variable definition does not call any operation that is not trivial
  */
  template<typename T, typename... Args>
  struct IsTriviallyConstructible : BoolConstant<__is_trivially_constructible(T, Args...)>
  {
    // Both MSVC & Clang use builtins for this
  };

  /*
  * Helper to access ::Value of IsTriviallyConstructible
  */
  template<typename T, typename... Args> 
  inline constexpr bool IsTriviallyConstructible_v = IsTriviallyConstructible<T, Args...>::Value;

  /*
  * True if IsConstructible and the variable definition is noexcept
  */
  template<typename T, typename... Args>
  struct IsNoThrowConstructible : BoolConstant<__is_nothrow_constructible(T, Args...)>
  {
    // Both MSVC & Clang use builtins for this
  };

  /*
  * Helper to access ::Value of IsNoThrowConstructible
  */
  template<typename T, typename... Args>
  inline constexpr bool IsNoThrowConstructible_v = IsNoThrowConstructible<T, Args...>::Value;

  /*
  * True if T is constructible without arguments
  */
  template<typename T>
  struct IsDefaultConstructible : IsConstructible<T> {};

  /*
  * Helper to acess ::Value of IsDefaultConstructible
  */
  template<typename T> inline constexpr bool IsDefaultConstructible_v = IsDefaultConstructible<T>::Value;

  /*
  * True if T is trivially constructible without arguments
  */
  template<typename T>
  struct IsTriviallyDefaultConstructible : IsTriviallyConstructible<T> {};

  /*
  * Helper to acess ::Value of IsTriviallyDefaultConstructible
  */
  template<typename T> 
  inline constexpr bool IsTriviallyDefaultConstructible_v = IsTriviallyDefaultConstructible<T>::Value;

  /*
  * True if T is nothrow constructible without arguments
  */
  template<typename T>
  struct IsNoThrowDefaultConstructible : IsNoThrowConstructible<T> {};

  /*
  * Helper to acess ::Value of IsNoThrowDefaultConstructible
  */
  template<typename T>
  inline constexpr bool IsNoThrowDefaultConstructible_v = IsNoThrowDefaultConstructible<T>::Value;

  /*
  * True if T can be copy-initialised with {}
  * Required for Tuple
  */
  template<typename T, typename=void>
  struct IsImplicitlyDefaultConstructible : FalseType {};
  template<typename T>
  struct IsImplicitlyDefaultConstructible<T, Void_t<decltype(ImplicitlyDefaultConstructibleHelper<T>({}))>> : TrueType {};

  /*
  * True if T is a referenceable type and copy-constructor is not deleted on T
  * Equal to IsConstructible<T, const T&>
  */
  template<typename T>
  struct IsCopyConstructible : BoolConstant<__is_constructible(T, AddLValueReference_t<const T>)> {};

  /*
  * Helper to access ::Value of IsCopyConstructible
  */
  template<typename T> inline constexpr bool IsCopyConstructible_v = IsCopyConstructible<T>::Value;

  /*
  * True if T is CopyConstructible, and also trivially constructible
  * Equal to IsTriviallyConstructible<T, const T&>
  */
  template<typename T>
  struct IsTriviallyCopyConstructible 
    : BoolConstant<__is_trivially_constructible(T, AddLValueReference_t<const T>)> {};

  /*
  * Helper to access ::Value of IsTriviallyCopyConstructible
  */
  template<typename T> 
  inline constexpr bool IsTriviallyCopyConstructible_v = IsTriviallyCopyConstructible<T>::Value;

  /*
  * True if T is CopyConstructible, and also nothrow constructible
  * Equal to IsNoThrowConstructible<T, const T&>
  */
  template<typename T>
  struct IsNoThrowCopyConstructible
    : BoolConstant<__is_nothrow_constructible(T, AddLValueReference_t<const T>)> {};

  /*
  * Helper to access ::Value of IsNoThrowCopyConstructible
  */
  template<typename T>
  inline constexpr bool IsNoThrowCopyConstructible_v = IsNoThrowCopyConstructible<T>::Value;

  /*
  * True if T is a referenceable type and move-constructor is not deleted on T
  * Equal to IsConstructible<T, T&&>
  */
  template<typename T>
  struct IsMoveConstructible : BoolConstant<__is_constructible(T, AddRValueReference_t<T>)> {};

  /*
  * Helper to access ::Value of IsMoveConstructible
  */
  template<typename T> inline constexpr bool IsMoveConstructible_v = IsMoveConstructible<T>::Value;

  /*
  * True if T is MoveConstructible, and also trivially constructible
  * Equal to IsTriviallyConstructible<T, T&&>
  */
  template<typename T>
  struct IsTriviallyMoveConstructible
    : BoolConstant<__is_trivially_constructible(T, AddRValueReference_t<T>)> {};

  /*
  * Helper to access ::Value of IsTriviallyMoveConstructible
  */
  template<typename T>
  inline constexpr bool IsTriviallyMoveConstructible_v = IsTriviallyMoveConstructible<T>::Value;

  /*
  * True if T is MoveConstructible, and also nothrow constructible
  * Equal to IsNoThrowConstructible<T, const T&>
  */
  template<typename T>
  struct IsNoThrowMoveConstructible
    : BoolConstant<__is_nothrow_constructible(T, AddRValueReference_t<T>)> {};

  /*
  * Helper to access ::Value of IsNoThrowMoveConstructible
  */
  template<typename T>
  inline constexpr bool IsNoThrowMoveConstructible_v = IsNoThrowMoveConstructible<T>::Value;

}

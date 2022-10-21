module;
export module autl.type_traits.isdestructible;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * True if T is destructible
  * False for void, function types, arrays of unknown bounds
  * True for reference types and objects where Declval<T&>().~T() is well-formed (it has a valid destructor)
  */
  template<typename T> struct IsDestructible : BoolConstant<__is_destructible(T)> {};

  /*
  * Helper to access ::Value of IsDestructible
  */
  template<typename T> inline constexpr bool IsDestructible_v = IsDestructible<T>::Value;

  /*
  * True if T is destructible according to IsDestructible, 
  * and also T is either a non-class type or a class type with a trivial (default, non user-defined) destructor 
  */
  template<typename T> struct IsTriviallyDestructible : BoolConstant<__is_trivially_destructible(T)> {};

  /*
  * Helper to access ::Value of IsTriviallyDestructible
  */
  template<typename T> inline constexpr bool IsTriviallyDestructible_v = IsTriviallyDestructible<T>::Value;

  /*
  * True if T is destructible according to IsDestructible
  * and also the destructor is noexcept
  */
  template<typename T> struct IsNoThrowDestructible : BoolConstant<__is_nothrow_destructible(T)> {};

  /*
  * Helper to access ::Value of IsNoThrowDestructible
  */
  template<typename T> inline constexpr bool IsNoThrowDestructible_v = IsNoThrowDestructible<T>::Value;
}

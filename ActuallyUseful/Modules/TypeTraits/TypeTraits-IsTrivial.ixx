module;
export module autl.type_traits.istrivial;

import autl.type_traits.integralconstant;
import autl.type_traits.isconstructible;

export namespace autl
{
  /*
  * True if T is trivially copyable
  */
  template<typename T>
  struct IsTriviallyCopyable : BoolConstant<__is_trivially_copyable(T)> {};

  /*
  * Helper to access ::Value of IsTriviallyCopyable
  */
  template<typename T> inline constexpr bool IsTriviallyCopyable_v = IsTriviallyCopyable<T>::Value;

  /*
  * True if T is trivially copyable and trivially default constructible
  */
  template<typename T>
  struct IsTrivial : BoolConstant<IsTriviallyCopyable_v<T> && IsTriviallyDefaultConstructible_v<T>> {};

  /*
  * Helper to access ::Value of IsTrivial
  */
  template<typename T> inline constexpr bool IsTrivial_v = IsTrivial<T>::Value;

}
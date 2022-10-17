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
  * Trivial types are:
  * - scalar types (arithmetic, enum, pointer, pointer-to-member)
  * - trivial class types (trivially copyable, & has at least one default constructor that is trivial)
  * - arrays of the above types
  * - cv-qualified versions of the above types
  */
  template<typename T>
  struct IsTrivial : BoolConstant<IsTriviallyCopyable_v<T> && IsTriviallyDefaultConstructible_v<T>> {};

  /*
  * Helper to access ::Value of IsTrivial
  */
  template<typename T> inline constexpr bool IsTrivial_v = IsTrivial<T>::Value;

}
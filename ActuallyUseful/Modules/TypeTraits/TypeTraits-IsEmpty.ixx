module;
export module autl.type_traits.isempty;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determine if T is an empty type
  * A type is empty if it is a non-union type with no non-static data other that bit fields of size 0
  * Has no virtual functions, no virtual base classes, and no non-empty base classes
  * Undefined for unions
  */
  template<typename T> struct IsEmpty : BoolConstant<__is_empty(T)> {};

  /*
  * Helper to access ::Value of IsEmpty
  */
  template<typename T> inline constexpr bool IsEmpty_v = IsEmpty<T>::Value;
}

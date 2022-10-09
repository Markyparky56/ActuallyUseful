module;
export module autl.type_traits.isunion;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determines if given type is a union
  */
  template<typename T> struct IsUnion : BoolConstant<__is_union(T)> {};

  /*
  * Helper to access ::Value of IsUnion
  */
  template<typename T> inline constexpr bool IsUnion_v = IsUnion<T>::Value;
}

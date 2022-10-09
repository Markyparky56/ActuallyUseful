module;
export module autl.type_traits.isenum;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determines if given type is an enum
  */
  template<typename T> struct IsEnum : BoolConstant<__is_enum(T)> {};

  /*
  * Helper to access ::Value of IsEnum
  */
  template<typename T> inline constexpr bool IsEnum_v = IsEnum<T>::Value;
}

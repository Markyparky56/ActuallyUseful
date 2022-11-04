module;
export module autl.type_traits.isenum;

import autl.type_traits.integralconstant;
import autl.type_traits.logical;
import autl.type_traits.convertible;

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

  /*
  * Determines if given type is a scoped enum
  */
  template<typename T> struct IsScopedEnum 
    : BoolConstant<Conjunction_v<IsEnum<T>, Negation<IsConvertible<T, int>>>> {};

  /*
  * Helper to access ::Value of IsScopedEnum
  */
  template<typename T> inline constexpr bool IsScopedEnum_v = IsScopedEnum<T>::Value;
}

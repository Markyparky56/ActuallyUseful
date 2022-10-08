module;
export module autl.type_traits.isfloatingpoint;

import autl.type_traits.logical;
import autl.type_traits.integralconstant;
import autl.type_traits.constvolatile;

export namespace autl
{
  /*
  * Is given type T any of the floating point types
  */
  export template<typename T> struct IsFloatingPoint
    : BoolConstant<IsAnyOf_v<RemoveCV_t<T>
    , float
    , double, long double>> {};

  /*
  * Helper to access ::Value of IsFloatingPoint
  */
  export template<typename T> inline constexpr bool IsFloatingPoint_v = IsFloatingPoint<T>::Value;
}

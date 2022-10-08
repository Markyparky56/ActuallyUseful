module;
export module autl.type_traits.isarithmetic;

import autl.type_traits.isintegral;
import autl.type_traits.isfloatingpoint;
import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Is given type T arithmetic (integral of floating point)?
  */
  export template<typename T> struct IsArithmetic : BoolConstant<IsIntegral_v<T> || IsFloatingPoint_v<T>> {};

  /*
  * Helper to access ::Value of IsArithmetic
  */
  export template<typename T> inline constexpr bool IsArithmetic_v = IsArithmetic<T>::Value;
}

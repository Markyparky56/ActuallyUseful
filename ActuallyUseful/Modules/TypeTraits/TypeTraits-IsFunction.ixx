module;
export module autl.type_traits.isfunction;

import autl.type_traits.integralconstant;
import autl.type_traits.constvolatile;
import autl.type_traits.reference;

export namespace autl
{
  /*
  * Determines if given type is a function type
  */
  template<typename T> struct IsFunction : BoolConstant<!IsConst_v<const T> && !IsReference_v<T>>
  {
    // Function types and Reference types cannot be const qualified
  };

  /*
  * Helper to access ::Value of IsFunction
  */
  template<typename T> inline constexpr bool IsFunction_v = IsFunction<T>::Value;
}

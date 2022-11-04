module;
export module autl.type_traits.isfinal;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determine is T is a final class
  * Final classes are classes with the final specifier that cannot be used as base classes
  */
  template<typename T> struct IsFinal : BoolConstant<__is_final(T)> {};

  /*
  * Helper to access ::Value of IsFinal
  */
  template<typename T> inline constexpr bool IsFinal_v = IsFinal<T>::Value;
}

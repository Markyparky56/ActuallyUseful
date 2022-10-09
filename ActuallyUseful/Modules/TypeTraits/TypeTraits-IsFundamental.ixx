module;
export module autl.type_traits.isfundamental;

import autl.type_traits.integralconstant;
import autl.type_traits.isarithmetic;
import autl.type_traits.isvoid;
import autl.type_traits.isnullptr;

export namespace autl
{
  /*
  * Determines if given type is a fundamental type
  * Fundamental types include:
  * - Arithmetic types (bool, char, int, float, etc.)
  * - Void
  * - nullptr
  */
  template<typename T> struct IsFundamental : BoolConstant<IsArithmetic_v<T> || IsVoid_v<T> || IsNullPointer_v<T>> {};

  /*
  * Helper to access ::Value of IsFundamental
  */
  template<typename T> inline constexpr bool IsFundamental_v = IsFundamental<T>::Value;
}

module;
export module autl.type_traits.isscalar;

import autl.type_traits.integralconstant;
import autl.type_traits.isarithmetic;
import autl.type_traits.isenum;
import autl.type_traits.pointer;
import autl.type_traits.isnullptr;

export namespace autl
{
  /*
  * Determine if type is a scalar type
  * Scalar types are:
  * - Arithemetic
  * - Enums
  * - Pointers & Member Pointers
  * - Null Pointers
  */
  template<typename T> struct IsScalar
    : BoolConstant<IsArithmetic_v<T> || IsEnum_v<T> || IsPointer_v<T> || IsMemberPointer_v<T> || IsNullPointer_v<T>>
  {};

  /*
  * Helper to access ::Value of IsScalar
  */
  template<typename T> inline constexpr bool IsScalar_v = IsScalar<T>::Value;
}

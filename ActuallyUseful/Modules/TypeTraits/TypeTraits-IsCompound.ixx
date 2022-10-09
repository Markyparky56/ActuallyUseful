module;
export module autl.type_traits.iscompound;

import autl.type_traits.integralconstant;
import autl.type_traits.isfundamental;

export namespace autl
{
  /*
  * Determine is type is a compound type
  * Compound types are non-fundamental types, including:
  * - Array
  * - Function
  * - Object ptr & Member Object ptr
  * - Function ptr & Member Function ptr
  * - Reference
  * - Class
  * - Union
  * - Enum
  */
  template<typename T> struct IsCompound : BoolConstant<!IsFundamental_v<T>> {};

  /*
  * Helper to access ::Value of IsCompound
  */
  template<typename T> inline constexpr bool IsCompound_v = IsCompound<T>::Value;
}

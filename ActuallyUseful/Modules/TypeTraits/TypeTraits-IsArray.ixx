module;
export module autl.type_traits.isarray;

import autl.type_traits.integralconstant;
import autl.types.std;

export namespace autl
{
  /*
  * Checks whether T is an array type
  * Doesn't not counter container arrays
  */
  template<typename T> struct IsArray : FalseType {};
  template<typename T> struct IsArray<T[]> : TrueType {};
  template<typename T, size_t N> struct IsArray<T[N]> : TrueType {};

  /*
  * Helper to access ::Value of IsArray
  */
  template<typename T> inline constexpr bool IsArray_v = IsArray<T>::Value;
}

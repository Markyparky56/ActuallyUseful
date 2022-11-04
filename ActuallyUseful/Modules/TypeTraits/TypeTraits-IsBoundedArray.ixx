module;
export module autl.type_traits.isboundedarray;

import autl.types.std;
import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determine if T is an array with known bounds
  */
  template<typename> struct IsBoundedArray : FalseType {};
  template<typename T, size_t N> struct IsBoundedArray<T[N]> : TrueType {};

  /*
  * Helper to access ::Value of IsBoundedArray
  */
  template<typename T> inline constexpr bool IsBoundedArray_v = IsBoundedArray<T>::Value;

  /*
  * Determine if T is an array with unknown bounds
  */
  template<typename> struct IsUnboundedArray : FalseType {};
  template<typename T> struct IsUnboundedArray<T[]> : TrueType {};

  /*
  * Helper to access ::Value of IsUnboundedArray
  */
  template<typename T> inline constexpr bool IsUnboundedArray_v = IsUnboundedArray<T>::Value;
}

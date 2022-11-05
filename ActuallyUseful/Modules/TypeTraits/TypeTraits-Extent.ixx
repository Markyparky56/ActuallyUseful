module;
export module autl.type_traits.extent;

import autl.types.std;
import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determines the number of elements along the Nth dimension of an array
  * For non-array types, is 0
  * If bounds unknown, is 0
  * If N is outside array bounds, is 0
  */
  template<typename T, unsigned int N = 0> struct Extent : IntegralConstant<size_t, 0> {};
  template<typename T> struct Extent<T[], 0> : IntegralConstant<size_t, 0> {};
  template<typename T, unsigned int N> struct Extent<T[], N> : Extent<T, N-1> {};
  template<typename T, size_t I> struct Extent<T[I], 0> : IntegralConstant<size_t, I> {};
  template<typename T, size_t I, unsigned int N> struct Extent<T[I], N> : Extent<T, N-1> {};

  /*
  * Helper to access ::Value of Extent
  */
  template<typename T, unsigned int N=0> inline constexpr size_t Extent_v = Extent<T, N>::Value;
}

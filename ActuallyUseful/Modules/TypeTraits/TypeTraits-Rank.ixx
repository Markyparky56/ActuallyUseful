module;
export module autl.type_traits.rank;

import autl.types.std;
import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * If T is an array type, provides the number of dimensions of the array
  * For all other types, value is 0
  */
  template<typename T> struct Rank : IntegralConstant<size_t, 0> {};
  template<typename T> struct Rank<T[]> : IntegralConstant<size_t, Rank<T>::Value + 1>{};
  template<typename T, size_t N> struct Rank<T[N]> : IntegralConstant<size_t, Rank<T>::Value + 1>{};

  /*
  * Helper to access ::Value of Rank
  */
  template<typename T> inline constexpr size_t Rank_v = Rank<T>::Value;
}

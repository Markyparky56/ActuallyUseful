module;
// Necessary evil
#include <initializer_list>
export module autl.type_traits.iscontiguous;

import autl.type_traits.integralconstant;
import autl.types.std;

export namespace autl
{
  /*
  * Determine if T is contiguous, meaning there are breaks in it's range
  * Requires [0..N) is valid
  */
  template<typename T> struct IsContiguous                     : FalseType {};
  template<typename T> struct IsContiguous<               T& > : FalseType {};
  template<typename T> struct IsContiguous<               T&&> : FalseType {};
  template<typename T> struct IsContiguous<const          T  > : FalseType {};
  template<typename T> struct IsContiguous<      volatile T  > : FalseType {};
  template<typename T> struct IsContiguous<const volatile T  > : FalseType {};
  
  /*
  * Determine if T is contiguous, meaning there are breaks in it's range
  * Requires [0..N) is valid
  * 
  * C-Array specialisations (always contiguous)
  */
  template<typename T, size_t N> struct IsContiguous<T[N]> : TrueType {};
  template<typename T, size_t N> struct IsContiguous<const T[N]> : TrueType {};
  template<typename T, size_t N> struct IsContiguous<volatile T[N]> : TrueType {};
  template<typename T, size_t N> struct IsContiguous<const volatile T[N]> : TrueType {};


  /*
  * Determine if T is contiguous, meaning there are breaks in it's range
  * Requires [0..N) is valid
  *
  * std::initializer_list specialisation (always contiguous)
  */
  template<typename T> struct IsContiguous<std::initializer_list<T>> : TrueType {};

  /*
  * Helper to access ::Value of IsContiguous
  */
  template<typename T> inline constexpr bool IsContiguous_v = IsContiguous<T>::Value;
}

module;
export module autl.type_traits.rangepointertype;

import autl.concepts.supportsbegin;
import autl.utility.declval;
import autl.types.std;

export namespace autl
{
  /*
  * Retrieve the element type of a range as a pointer to that type, available as ::Type
  * Expects RangeType to implement .begin()
  */
  template<typename RangeType>
    requires SupportsBegin<RangeType>
  struct RangePointerType { using Type = decltype(&*Declval<RangeType&>().begin()); };

  /*
  * RangePointerType specialisation for single-dimension sized array objects
  * Retrieves the element type, available as ::Type
  */
  template<typename T, size_t N> 
  struct RangePointerType<T[N]> { using Type = T*; };


  /*
  * Helper to access ::Type of RangePointerType
  */
  template<typename T> using RangePointerType_t = typename RangePointerType<T>::Type;
}
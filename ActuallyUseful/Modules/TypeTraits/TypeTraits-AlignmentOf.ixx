module;
export module autl.type_traits.alignmentof;

import autl.types.std;
import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Provides the alignment requirement for type T as if obtained by an alignof expression
  * If T is an array type, returns the alignment requirement for the element type
  * If T is a reference type, returns the alignment requirement of the type referred to
  */
  template<typename T> struct AlignmentOf : IntergralConstant<size_t, alignof(T)> {};

  /*
  * Helper to access ::Value of AlignmentOf
  */
  template<typename T> inline constexpr size_t AlignmentOf_v = AlignmentOf<T>::Value;
}

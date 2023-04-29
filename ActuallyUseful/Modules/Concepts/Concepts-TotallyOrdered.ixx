module;
export module autl.concepts.totallyordered;

import "Internal-BooleanTestable.h";
import autl.concepts.equalitycomparable;
import autl.type_traits.commonreference;
import autl.type_traits.reference;

namespace autl
{
  template<typename A, typename B>
  concept PartiallyOrderedWith =
    requires(MakeConstLValueRef<A> a, MakeConstLValueRef<B> b)
    {
      { a <  b } -> BooleanTestable;
      { a >  b } -> BooleanTestable;
      { a <= b } -> BooleanTestable;
      { a >= b } -> BooleanTestable;
      { b <  a } -> BooleanTestable;
      { b >  a } -> BooleanTestable;
      { b <= a } -> BooleanTestable;
      { b >= a } -> BooleanTestable;
  };
}

export namespace autl
{
  /*
  * Specify that the comparison operators ==, !=, <, >, <=, >= on a type yield results consistent with strict ordering
  */
  template<typename T>
  concept TotallyOrdered = EqualityComparable<T> && PartiallyOrderedWith<T, T>;

  /*
  * Specify that the comparison operators ==, !=, <, >, <=, >= on types T and U yield results consistent with strict ordering
  */
  template<typename A, typename B>
  concept TotallyOrderedWith = 
       TotallyOrdered<A>
    && TotallyOrdered<B>
    && EqualityComparableWith<A, B>
    && TotallyOrdered<CommonReference_t<MakeConstLValueRef<A>, MakeConstLValueRef<B>>>
    && PartiallyOrderedWith<A, B>
    ;
}

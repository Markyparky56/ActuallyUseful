module;
export module autl.concepts.equalitycomparable;

import "Internal-BooleanTestable.h";
import autl.concepts.convertibleto;
import autl.concepts.commonreference;
import autl.type_traits.reference;
import autl.type_traits.commonreference;
import autl.utility.forward;

namespace autl
{
  // Define that A and B must be comparable by the == and != operators
  template<typename A, typename B> concept HalfEqualityComparable = 
    requires(const RemoveReference_t<A>& a, const RemoveReference_t<B>& b) {
      { a == b } -> BooleanTestable;
      { a != b } -> BooleanTestable;
    };

  // Define that A and B must be comparable via == and != operators irrespective of ordering
  // a == b, b == a, a != b, b != a
  template<typename A, typename B> concept WeaklyEqualityComparableWith =
    HalfEqualityComparable<A, B> && HalfEqualityComparable<B, A>;
}

export namespace autl
{
  /*
  * Specify that T must be comparable such that the == operator returns true if the operands are equal
  */
  template<typename T> concept EqualityComparable = WeaklyEqualityComparableWith<T, T>;

  /*
  * Specify that the == and != operators on A and B yield results consistent with equality
  */
  template<typename A, typename B> concept EqualityComparableWith = 
       EqualityComparable<A> && EqualityComparable<B>
    && CommonReferenceWith<MakeConstLValueRef<A>, MakeConstLValueRef<B>>
    && EqualityComparable<CommonReference_t<MakeConstLValueRef<A>, CommonReference_t<B>>>
    && WeaklyEqualityComparableWith<A, B>;
}

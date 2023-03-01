module;
export module autl.concepts.equalitycomparable;

import autl.concepts.convertibleto;
import autl.type_traits.reference;
import autl.utility.forward;

namespace autl
{
  // Define that T must be convertible to a bool
  template<typename T> concept BooleanTestableHelper = ConvertibleTo<T, bool>;
  template<typename T> concept BooleanTestable =
       BooleanTestableHelper<T>
    && requires(T&& t) { {!Forward<T>(t) } -> BooleanTestableHelper; };

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
  //template<typename A, typename B> concept EqualityComparable = 
  //     WeaklyEqualityComparableWith<A, B>
  //  && TODO: CommonReference_t
}

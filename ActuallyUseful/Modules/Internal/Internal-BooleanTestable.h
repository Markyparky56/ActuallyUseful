#pragma once
// Required by both EqualityComparable and TotallyOrdered. Provided via internal header unit rather than export

import autl.concepts.convertibleto;

namespace autl
{
  // Define that T must be convertible to a bool
  template<typename T> concept BooleanTestableHelper = ConvertibleTo<T, bool>;
  template<typename T> concept BooleanTestable =
    BooleanTestableHelper<T>
    && requires(T&& t) { { !static_cast<T&&>(t) } -> BooleanTestableHelper; };
}

#include "pch.h"
#include <concepts>

import autl.concepts;

TEST(Concepts, ConvertibleTo)
{
  constexpr bool intint = autl::ConvertibleTo<int, int>;
  EXPECT_TRUE(intint);
  static_assert(intint);

  constexpr bool shortRefShortConstRef = autl::ConvertibleTo<short&, short const&>;
  EXPECT_TRUE(shortRefShortConstRef);
  static_assert(shortRefShortConstRef);

  constexpr bool intshort = autl::ConvertibleTo<int, short>;
  EXPECT_TRUE(intint);
  static_assert(intshort);

  constexpr bool intRefShortRef = autl::ConvertibleTo<int&, short&>;
  EXPECT_FALSE(intRefShortRef);
  static_assert(!intRefShortRef);

  constexpr bool intvoid = autl::ConvertibleTo<int, void>;
  EXPECT_FALSE(intvoid);
  static_assert(!intvoid);

  constexpr bool intintRef = autl::ConvertibleTo<int, int&>;
  EXPECT_FALSE(intintRef);
  static_assert(!intintRef);
}

// Borrowed from range-v3, https://github.com/ericniebler/range-v3/blob/master/test/utility/concepts.cpp
struct IntComparable
{
  operator int() const;

  friend bool operator==(IntComparable, IntComparable);
  friend bool operator!=(IntComparable, IntComparable);

  friend bool operator<(IntComparable, IntComparable);
  friend bool operator>(IntComparable, IntComparable);
  friend bool operator<=(IntComparable, IntComparable);
  friend bool operator>=(IntComparable, IntComparable);

  friend bool operator==(int, IntComparable);
  friend bool operator!=(int, IntComparable);
  friend bool operator==(IntComparable, int);
  friend bool operator!=(IntComparable, int);

  friend bool operator<(int, IntComparable);
  friend bool operator<(IntComparable, int);
  friend bool operator>(int, IntComparable);
  friend bool operator>(IntComparable, int);
  friend bool operator<=(int, IntComparable);
  friend bool operator<=(IntComparable, int);
  friend bool operator>=(int, IntComparable);
  friend bool operator>=(IntComparable, int);
};

TEST(Concepts, TotallyOrdered)
{
  constexpr bool intTotallyOrdered = autl::TotallyOrdered<int>;
  EXPECT_TRUE(intTotallyOrdered);
  // static_assert(intTotallyOrdered); // fails in Release?
}

TEST(Concepts, CommonWith)
{
  constexpr bool commonIntComparable = autl::CommonWith<int, IntComparable>;
  constexpr bool commonIntComparable2 = std::common_with<int, IntComparable>;
  EXPECT_TRUE(commonIntComparable);
  static_assert(commonIntComparable); // Intellisense reports false, compiler passes (debug & release)
}

TEST(Concepts, CommonReferenceWith)
{
  constexpr bool commonIntComparable = autl::CommonReferenceWith<int, IntComparable>;
  constexpr bool commonIntComparable2 = std::common_reference_with<int, IntComparable>;
  EXPECT_TRUE(commonIntComparable);
  static_assert(commonIntComparable); // Intellisense reports false, compiler passes (debug & release)
}

TEST(Concepts, TotallyOrderedWithAB)
{
  constexpr bool totallyOrderedWithAB = autl::TotallyOrderedWith<int, IntComparable>;
  constexpr bool totallyOrderedWithAB2 = std::totally_ordered_with<int, IntComparable>;
  EXPECT_TRUE(totallyOrderedWithAB);
  // static_assert(totallyOrderedWithAB); // Intellisense reports false, compiler passes debug, fails release
}

TEST(Concepts, TotallyOrderedWithBA)
{
  constexpr bool totallyOrderedWithBA = autl::TotallyOrderedWith<IntComparable, int>;
  constexpr bool totallyOrderedWithBA2 = std::totally_ordered_with<IntComparable, int>;
  EXPECT_TRUE(totallyOrderedWithBA);
  // static_assert(totallyOrderedWithBA); // Intellisense reports false, compiler passes debug, fails release
}

TEST(Concepts, WeaklyEqualityComparableWith)
{
  constexpr bool weaklyComparableWith = autl::WeaklyEqualityComparableWith<int, int>;
  constexpr bool weaklyComparableWith2 = std::_Weakly_equality_comparable_with<int, int>;
  EXPECT_TRUE(weaklyComparableWith);
  // static_assert(weaklyComparableWith); // Intellisense reports true, compiler passes debug, fails release
}

TEST(Concepts, EqualityComparable)
{
  constexpr bool equalityComparable = autl::EqualityComparable<int>;
  constexpr bool equalityComparable2 = std::equality_comparable<int>;
  EXPECT_TRUE(equalityComparable);
  // static_assert(equalityComparable); // Intellisense reports true, compiler passes debug, fails release
}

TEST(Concepts, EqualityComparableWith)
{
  constexpr bool equalityComparableWith_intint = autl::EqualityComparableWith<int, int>;
  constexpr bool equalityComparableWith_intint2 = std::equality_comparable_with<int, int>;
  EXPECT_TRUE(equalityComparableWith_intint);
  // static_assert(equalityComparableWith_intint); // Intellisense reports false, compiler passes debug, fails release

  constexpr bool equalityComparableWith_intintcomparable = autl::EqualityComparableWith<int, IntComparable>;
  constexpr bool equalityComparableWith_intintcomparable2 = std::equality_comparable_with<int, IntComparable>;
  EXPECT_TRUE(equalityComparableWith_intint);
  // static_assert(equalityComparableWith_intintcomparable); // Intellisense reports false, compiler passes debug, fails release

  constexpr bool equalityComparableWith_intintcomparable_ref= autl::EqualityComparableWith<int&, IntComparable&>;
  constexpr bool equalityComparableWith_intintcomparable_ref2 = std::equality_comparable_with<int&, IntComparable&>;
  EXPECT_TRUE(equalityComparableWith_intintcomparable_ref);
  // static_assert(equalityComparableWith_intintcomparable_ref); // Intellisense reports false, compiler passes debug, fails release
}

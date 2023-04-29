#include "pch.h"
#include <concepts>

import autl.concepts;

TEST(Concepts, ConvertibleTo)
{
  constexpr bool intint = autl::ConvertibleTo<int, int>;
  EXPECT_TRUE(intint);

  constexpr bool shortRefShortConstRef = autl::ConvertibleTo<short&, short const&>;
  EXPECT_TRUE(shortRefShortConstRef);

  constexpr bool intshort = autl::ConvertibleTo<int, short>;
  EXPECT_TRUE(intint);

  constexpr bool intRefShortRef = autl::ConvertibleTo<int&, short&>;
  EXPECT_FALSE(intRefShortRef);

  constexpr bool intvoid = autl::ConvertibleTo<int, void>;
  EXPECT_FALSE(intvoid);

  constexpr bool intintRef = autl::ConvertibleTo<int, int&>;
  EXPECT_FALSE(intintRef);
}

// Borrowed from range-v3
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
  EXPECT_TRUE(autl::TotallyOrdered<int>);
}

TEST(Concepts, CommonWith)
{
  constexpr bool commonIntComparable = autl::CommonWith<int, IntComparable>;
  constexpr bool commonIntComparable2 = std::common_with<int, IntComparable>;
  EXPECT_TRUE(commonIntComparable);
}

TEST(Concepts, CommonReferenceWith)
{
  constexpr bool commonIntComparable = autl::CommonReferenceWith<int, IntComparable>;
  constexpr bool commonIntComparable2 = std::common_reference_with<int, IntComparable>;
  EXPECT_TRUE(commonIntComparable);
}

TEST(Concepts, TotallyOrderedWithAB)
{
  constexpr bool totallyOrderedWithAB = autl::TotallyOrderedWith<int, IntComparable>;
  constexpr bool totallyOrderedWithAB2 = std::totally_ordered_with<int, IntComparable>;
  EXPECT_TRUE(totallyOrderedWithAB);
}

TEST(Concepts, TotallyOrderedWithBA)
{
  constexpr bool totallyOrderedWithBA = autl::TotallyOrderedWith<IntComparable, int>;
  constexpr bool totallyOrderedWithBA2 = std::totally_ordered_with<IntComparable, int>;
  EXPECT_TRUE(totallyOrderedWithBA);
}

TEST(Concepts, WeaklyEqualityComparableWith)
{
  constexpr bool weaklyComparableWith = autl::WeaklyEqualityComparableWith<int, int>;
  constexpr bool weaklyComparableWith2 = std::_Weakly_equality_comparable_with<int, int>;
  EXPECT_TRUE(weaklyComparableWith);
}

TEST(Concepts, EqualityComparable)
{
  constexpr bool equalityComparable = autl::EqualityComparable<int>;
  constexpr bool equalityComparable2 = std::equality_comparable<int>;
  EXPECT_TRUE(equalityComparable);
}

TEST(Concepts, EqualityComparableWith)
{
  constexpr bool equalityComparableWith_intint = autl::EqualityComparableWith<int, int>;
  constexpr bool equalityComparableWith_intint2 = std::equality_comparable_with<int, int>;
  EXPECT_TRUE(equalityComparableWith_intint);

  constexpr bool equalityComparableWith_intintcomparable = autl::EqualityComparableWith<int, IntComparable>;
  constexpr bool equalityComparableWith_intintcomparable2 = std::equality_comparable_with<int, IntComparable>;
  EXPECT_TRUE(equalityComparableWith_intint);

  constexpr bool equalityComparableWith_intintcomparable_ref= autl::EqualityComparableWith<int&, IntComparable&>;
  constexpr bool equalityComparableWith_intintcomparable_ref2 = std::equality_comparable_with<int&, IntComparable&>;
  EXPECT_TRUE(equalityComparableWith_intintcomparable_ref);
}

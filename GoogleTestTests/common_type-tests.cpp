#include "pch.h"

#include <type_traits>

import autl.type_traits;

// Borrowed from https://en.cppreference.com/w/cpp/types/common_type
template<typename T>
struct CommonNumber { T n; };
template<typename T, typename U>
CommonNumber<autl::CommonType_t<T, U>> operator+(const CommonNumber<T>& lhs, const CommonNumber<U>& rhs)
{
  return { lhs.n + rhs.n };
}

TEST(TypeTraitsTests, CommonType)
{
  CommonNumber<int> i1 = { 1 }, i2 = { 2 };
  CommonNumber<double> d1 = { 2.3 }, d2 = { 3.5 };

  auto sumIs = (i1 + i2).n;
  auto sumDs = (d1 + d2).n;
  auto sumI1D1 = (i1 + d1).n;
  auto sumI2D2 = (i2 + d2).n;

  EXPECT_EQ(sumIs, 3);
  EXPECT_EQ(sumDs, 5.8);
  EXPECT_EQ(sumI1D1, 3.3);
  EXPECT_EQ(sumI2D2, 5.5);
}

// Borrowing from https://github.com/ericniebler/range-v3/blob/master/test/utility/common_type.cpp

struct B {};
struct D : B {};

TEST(TypeTraitsTests, CommonReferenceBasic)
{
  {
    using T = autl::CommonReference_t<B&, D&>;
    using T2 = std::common_reference_t<B&, D&>;
    constexpr bool issame = autl::IsSame_v<T, B&>;
    EXPECT_TRUE(issame);
  }
  {
    using T = autl::CommonReference_t<B&, const D&>;
    using T2 = std::common_reference_t<B&, const D&>;
    constexpr bool issame = autl::IsSame_v<T, const B&>;
    EXPECT_TRUE(issame);
  }
  {
    using T = autl::CommonReference_t<const B&, const D&>;
    using T2 = std::common_reference_t<const B&, const D&>;
    constexpr bool issame = autl::IsSame_v<T, const B&>;
    EXPECT_TRUE(issame);
  }
}

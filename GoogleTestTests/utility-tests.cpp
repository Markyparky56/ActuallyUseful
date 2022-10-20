#include "pch.h"

import autl.utility;
import autl.types;

TEST(UtilityTests, Exchange)
{
  struct A
  {
    int v[4];
  };

  A a;
  a.v[0] = 1; a.v[1] = 2; a.v[2] = 3; a.v[3] = 4;

  A b;
  autl::Exchange(b, a);

  EXPECT_EQ(b.v[0], 1);
  EXPECT_EQ(b.v[1], 2);
  EXPECT_EQ(b.v[2], 3);
  EXPECT_EQ(b.v[3], 4);
}

TEST(UtilityTests, Swap)
{
  int a = 1;
  int b = 2;

  autl::Swap(a, b);

  EXPECT_EQ(a, 2);
  EXPECT_EQ(b, 1);

  struct A
  {
    int a, b, c;
  };
  A a1, a2;
  a1.a = 10;
  a1.b = 20;
  a1.c = 30;
  a2.a = -10;
  a2.b = -20;
  a2.c = -30;

  autl::Swap(a1, a2);

  EXPECT_EQ(a2.c, 30);
  EXPECT_EQ(a1.b, -20);

  // TODO: Extend once more complex structures are implemented like UniquePtr and Array that need custom swaps
}

TEST(UtilityTests, SwapArrays)
{
  int a[] = { 1,2,3,4 };
  int b[] = { 5,6,7,8 };

  autl::Swap(a, b);

  EXPECT_EQ(a[0], 5);
  EXPECT_EQ(b[3], 4);
}

TEST(UtilityTests, BitCast)
{
  constexpr double f64v = 19880124.0;
  constexpr autl::uint64 u64v = autl::BitCast<autl::uint64>(f64v);
  static_assert(autl::BitCast<double>(u64v) == f64v); // round-trip without loss of data
  EXPECT_EQ(autl::BitCast<double>(u64v), f64v);
}

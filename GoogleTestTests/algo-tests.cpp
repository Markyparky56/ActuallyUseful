#include "pch.h"
#include <vector>

import autl.algo;

TEST(AlgoTransformTests, TransformIfEven)
{
  std::vector<int> nums = { 1,2,3,4,5,6,7,8,9,10 };
  std::vector<int> evens;

  autl::TransformIf(nums, evens,
    [](const int i)->bool {
      return i % 2 == 0;
    },
    [](const int i)->int {
      return i;
    }
  );

  EXPECT_EQ(evens.size(), 5);
  if (evens.size() > 0)
  {
    for (int i = 0; i < 5; ++i)
    {
      const int expected = (i+1)*2;
      EXPECT_TRUE(evens[i] == expected);
    }
  }
}

TEST(AlgoTransformTests, TransformTimesTwo)
{
  std::vector<int> nums = { 1,2,3,4,5,6,7,8,9,10 };
  std::vector<int> out;

  autl::Transform(nums, out,
    [](const int i)->int {
      return i * 2;
    }
  );

  EXPECT_EQ(out.size(), nums.size());
  if (out.size() > 0)
  {
    for (int i = 0; i < nums.size(); ++i)
    {
      const int div2 = out[i] / 2;
      EXPECT_TRUE(div2 == nums[i]);
    }
  }
}

TEST(AlgoAllOfTests, Truthy)
{
  std::vector<bool> trues = { true, true, true, true };
  std::vector<bool> falses = { false, false, false, false };
  std::vector<bool> mixed = { true, false, true, false };

  EXPECT_TRUE(autl::AllOf(trues));
  EXPECT_FALSE(autl::AllOf(falses));
  EXPECT_FALSE(autl::AllOf(mixed));
}

TEST(AlgoAllOfTests, TruthyProjected)
{
  std::vector<int> evens = { 2, 4, 6, 8 };
  std::vector<int> odds = { 1, 3, 5, 7 };

  auto IsEven = [](const int i) { return i % 2 == 0; };
  auto IsOdd = [](const int i) { return i % 2 != 0; };

  EXPECT_TRUE(autl::AllOf(evens, IsEven));
  EXPECT_TRUE(autl::AllOf(odds, IsOdd));
}

TEST(AlgoNoneOfTests, Falsey)
{
  std::vector<bool> trues = { true, true, true, true };
  std::vector<bool> falses = { false, false, false, false };
  std::vector<bool> mixed = { true, false, true, false };

  EXPECT_FALSE(autl::NoneOf(trues));
  EXPECT_TRUE(autl::NoneOf(falses));
  EXPECT_FALSE(autl::NoneOf(mixed));
}

TEST(AlgoNoneOfTests, FalseyProjected)
{
  std::vector<int> evens = { 2, 4, 6, 8 };
  std::vector<int> odds = { 1, 3, 5, 7 };

  auto IsEven = [](const int i) { return i % 2 == 0; };
  auto IsOdd = [](const int i) { return i % 2 != 0; };

  EXPECT_FALSE(autl::NoneOf(evens, IsEven));
  EXPECT_TRUE(autl::NoneOf(evens, IsOdd));
  EXPECT_TRUE(autl::NoneOf(odds, IsEven));
  EXPECT_FALSE(autl::NoneOf(odds, IsOdd));
}

#include "pch.h"
#include <vector>

import autl.algo.transform;

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
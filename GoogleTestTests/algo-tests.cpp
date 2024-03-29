#include "pch.h"
#include <vector>
#include <span>

import autl.algo;
import autl.utility.begin;

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

TEST(AlgoAllOfTests, TruthyRValue)
{
  // Test r-value temporary input
  EXPECT_TRUE(autl::AllOf(std::vector<bool>{ true, true }));
  EXPECT_FALSE(autl::AllOf(std::vector<bool>{ true, false }));
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

TEST(AlgoNoneOfTests, FalseRValue)
{
  // Test r-value temporary input
  EXPECT_TRUE(autl::NoneOf(std::vector<bool>{ false, false }));
  EXPECT_FALSE(autl::NoneOf(std::vector<bool>{ true, false }));
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

TEST(AlgoAnyOfTests, AnyOf)
{
  std::vector<bool> trues = { true, true, true, true };
  std::vector<bool> falses = { false, false, false, false };
  std::vector<bool> mixed = { false, false, false, true };

  EXPECT_TRUE(autl::AnyOf(trues));
  EXPECT_FALSE(autl::AnyOf(falses));
  EXPECT_TRUE(autl::AnyOf(mixed));
}

TEST(AlgoAnyOfTests, AnyOfRValue)
{
  // Test r-value temporary input
  EXPECT_TRUE(autl::AnyOf(std::vector<bool>{ false, true }));
  EXPECT_FALSE(autl::AnyOf(std::vector<bool>{ false, false }));
}

TEST(AlgoAnyOfTests, AnyOfProj)
{
  std::vector<int> nums = { 1, 2, 3, 4 };
  std::vector<int> num2 = { 1, 3, 5, 7 };
  std::vector<int> num3 = { 2, 2, 2, 3 };

  auto IsEven = [](const int i) { return i % 2 == 0; };

  EXPECT_TRUE(autl::AnyOf(nums, IsEven));
  EXPECT_FALSE(autl::AnyOf(num2, IsEven));
  EXPECT_TRUE(autl::AnyOf(num3, [](const int i) {return i == 3; }));
}

TEST(AlgoMinElementTests, SimpleMinPointer)
{
  std::vector<int> nums = { 4, 2, 1, 3 };
  int* min = autl::MinElement(nums);
  EXPECT_EQ(*min, 1);

  int nums2[4] = { 4, 2, 1, 3 };
  int* min2 = autl::MinElement(nums2);
  EXPECT_EQ(*min2, 1);
}

TEST(AlgoMinElementTests, MinPointerPredicate)
{
  auto sortLess = [](const int lhs, const int rhs) { return lhs < rhs; };

  std::vector<int> nums = { 4, 2, 1, 3 };
  int* min = autl::MinElement(nums, sortLess);
  EXPECT_EQ(*min, 1);

  int nums2[4] = { 4, 2, 1, 3 };
  int* min2 = autl::MinElement(nums2, sortLess);
  EXPECT_EQ(*min2, 1);
}

TEST(AlgoMinElementTests, MinPointerProjection)
{
  auto projInvert = [](const int element) { return -element; };

  std::vector<int> nums = { 4, 2, 1, 3 };
  int* min = autl::MinElementBy(nums, projInvert);
  EXPECT_EQ(*min, 4);

  int nums2[4] = { 4, 2, 1, 3 };
  int* min2 = autl::MinElementBy(nums2, projInvert);
  EXPECT_EQ(*min2, 4);
}

TEST(AlgoMinElementTests, MinPointerProjectionPredicate)
{
  auto sortLess = [](const int lhs, const int rhs) { return lhs < rhs; };
  auto projInvert = [](const int element) { return -element; };

  std::vector<int> nums = { 4, 2, 1, 3 };
  int* min = autl::MinElementBy(nums, projInvert, sortLess);
  EXPECT_EQ(*min, 4);

  int nums2[4] = { 4, 2, 1, 3 };
  int* min2 = autl::MinElementBy(nums2, projInvert, sortLess);
  EXPECT_EQ(*min2, 4);
}

TEST(AlgoMinElementTests, SimpleMinIter)
{
  std::vector<int> nums = { 4, 2, 1, 3 };
  std::vector<int>::iterator min = autl::MinElement(nums.begin(), nums.end());
  EXPECT_EQ(*min, 1);

  int nums2[4] = { 4, 2, 1, 3 };
  int* min2 = autl::MinElement(nums2, nums2 + 4);
  EXPECT_EQ(*min2, 1);

  std::span<int> nums3(nums2);
  std::span<int>::iterator min3 = autl::MinElement(nums3.begin(), nums3.end());
  EXPECT_EQ(*min3, 1);
}

TEST(AlgoMinElementTests, MinIterPredicate)
{
  auto sortLess = [](const int lhs, const int rhs) { return lhs < rhs; };

  std::vector<int> nums = { 4, 2, 1, 3 };
  std::vector<int>::iterator min = autl::MinElement(nums.begin(), nums.end(), sortLess);
  EXPECT_EQ(*min, 1);

  int nums2[4] = { 4, 2, 1, 3 };
  int* min2 = autl::MinElement(nums2, nums2 + 4, sortLess);
  EXPECT_EQ(*min2, 1);

  std::span<int> nums3(nums2);
  std::span<int>::iterator min3 = autl::MinElement(nums3.begin(), nums3.end(), sortLess);
  EXPECT_EQ(*min3, 1);
}

TEST(AlgoMinElementTests, MinIterProjection)
{
  auto projInvert = [](const int element) { return -element; };

  std::vector<int> nums = { 4, 2, 1, 3 }; // -4, -2,  -1, -3
  std::vector<int>::iterator min = autl::MinElementBy(nums.begin(), nums.end(), projInvert);
  EXPECT_EQ(*min, 4);

  int nums2[4] = { 4, 2, 1, 3 };
  int* min2 = autl::MinElementBy(nums2, nums2 + 4, projInvert);
  EXPECT_EQ(*min2, 4);

  std::span<int> nums3(nums2);
  std::span<int>::iterator min3 = autl::MinElementBy(nums3.begin(), nums3.end(), projInvert);
  EXPECT_EQ(*min3, 4);
}

TEST(AlgoMinElementTests, MinIterProjectionPredicate)
{
  auto sortLess = [](const int lhs, const int rhs) { return lhs < rhs; };
  auto projInvert = [](const int element) { return -element; };

  std::vector<int> nums = { 4, 2, 1, 3 }; // -4, -2,  -1, -3
  std::vector<int>::iterator min = autl::MinElementBy(nums.begin(), nums.end(), projInvert, sortLess);
  EXPECT_EQ(*min, 4);

  int nums2[4] = { 4, 2, 1, 3 };
  int* min2 = autl::MinElementBy(nums2, nums2 + 4, projInvert, sortLess);
  EXPECT_EQ(*min2, 4);

  std::span<int> nums3(nums2);
  std::span<int>::iterator min3 = autl::MinElementBy(nums3.begin(), nums3.end(), projInvert, sortLess);
  EXPECT_EQ(*min3, 4);
}

TEST(AlgoMaxElementTests, SimpleMaxPointer)
{
  std::vector<int> nums = { 1, 2, 3, 4 };
  int* max = autl::MaxElement(nums);
  EXPECT_EQ(*max, 4);

  int nums2[4] = { 1, 2, 3, 4 };
  int* max2 = autl::MaxElement(nums2);
  EXPECT_EQ(*max2, 4);
}

TEST(AlgoMaxElementTests, MaxPointerPredicate)
{
  auto sortLess = [](const int lhs, const int rhs) { return lhs < rhs; };

  std::vector<int> nums = { 1, 2, 3, 4 };
  int* max = autl::MaxElement(nums, sortLess);
  EXPECT_EQ(*max, 4);

  int nums2[4] = { 1, 2, 3, 4 };
  int* max2 = autl::MaxElement(nums2, sortLess);
  EXPECT_EQ(*max2, 4);
}

TEST(AlgoMaxElementTests, MaxPointerProjection)
{
  auto projInvert = [](const int element) { return -element; };

  std::vector<int> nums = { 1, 2, 3, 4 };
  int* max = autl::MaxElementBy(nums, projInvert);
  EXPECT_EQ(*max, 1);

  int nums2[4] = { 1, 2, 3, 4 };
  int* max2 = autl::MaxElementBy(nums2, projInvert);
  EXPECT_EQ(*max2, 1);
}

TEST(AlgoMaxElementTests, MaxPointerProjectionPredicate)
{
  auto sortLess = [](const int lhs, const int rhs) { return lhs < rhs; };
  auto projInvert = [](const int element) { return -element; };

  std::vector<int> nums = { 1, 2, 3, 4 };
  int* max = autl::MaxElementBy(nums, projInvert, sortLess);
  EXPECT_EQ(*max, 1);

  int nums2[4] = { 1, 2, 3, 4 };
  int* max2 = autl::MaxElementBy(nums2, projInvert, sortLess);
  EXPECT_EQ(*max2, 1);
}

TEST(AlgoMaxElementTests, SimpleMaxIter)
{
  std::vector<int> nums = { 1, 2, 3, 4 };
  std::vector<int>::iterator max = autl::MaxElement(nums.begin(), nums.end());
  EXPECT_EQ(*max, 4);

  int nums2[4] = { 1, 2, 3, 4 };
  int* max2 = autl::MaxElement(nums2, nums2 + 4);
  EXPECT_EQ(*max2, 4);

  std::span<int> nums3(nums2);
  std::span<int>::iterator max3 = autl::MaxElement(nums3.begin(), nums3.end());
  EXPECT_EQ(*max3, 4);
}

TEST(AlgoMaxElementTests, MaxIterPredicate)
{
  auto sortLess = [](const int lhs, const int rhs) { return lhs < rhs; };

  std::vector<int> nums = { 1, 2, 3, 4 };
  std::vector<int>::iterator max = autl::MaxElement(nums.begin(), nums.end(), sortLess);
  EXPECT_EQ(*max, 4);

  int nums2[4] = { 1, 2, 3, 4 };
  int* max2 = autl::MaxElement(nums2, nums2 + 4, sortLess);
  EXPECT_EQ(*max2, 4);

  std::span<int> nums3(nums2);
  std::span<int>::iterator max3 = autl::MaxElement(nums3.begin(), nums3.end(), sortLess);
  EXPECT_EQ(*max3, 4);
}

TEST(AlgoMaxElementTests, MaxIterProjection)
{
  auto projInvert = [](const int element) { return -element; };

  std::vector<int> nums = { 1, 2, 3, 4 };
  std::vector<int>::iterator max = autl::MaxElementBy(nums.begin(), nums.end(), projInvert);
  EXPECT_EQ(*max, 1);

  int nums2[4] = { 1, 2, 3, 4 };
  int* max2 = autl::MaxElementBy(nums2, nums2 + 4, projInvert);
  EXPECT_EQ(*max2, 1);

  std::span<int> nums3(nums2);
  std::span<int>::iterator max3 = autl::MaxElementBy(nums3.begin(), nums3.end(), projInvert);
  EXPECT_EQ(*max3, 1);
}

TEST(AlgoMaxElementTests, MaxIterProjectionPredicate)
{
  auto sortLess = [](const int lhs, const int rhs) { return lhs < rhs; };
  auto projInvert = [](const int element) { return -element; };

  std::vector<int> nums = { 1, 2, 3, 4 };
  std::vector<int>::iterator max = autl::MaxElementBy(nums.begin(), nums.end(), projInvert, sortLess);
  EXPECT_EQ(*max, 1);

  int nums2[4] = { 1, 2, 3, 4 };
  int* max2 = autl::MaxElementBy(nums2, nums2 + 4, projInvert, sortLess);
  EXPECT_EQ(*max2, 1);

  std::span<int> nums3(nums2);
  std::span<int>::iterator max3 = autl::MaxElementBy(nums3.begin(), nums3.end(), projInvert, sortLess);
  EXPECT_EQ(*max3, 1);
}

TEST(AlgoIndexOfTests, ValidIndex)
{
  int nums[4] = {42, 123, 316, 1013};
  autl::size_t idx = autl::IndexOf(nums, 316);
  EXPECT_EQ(idx, 2);

  // Only valid std container that passes ContiguousRange for the moment
  // std::ranges has a ContiguousRange concept that works via iterators that should probably be integrated
  std::initializer_list<int> nums2{ 42, 123, 316, 1013 };
  autl::size_t idx2 = autl::IndexOf(nums2, 316);
  EXPECT_EQ(idx, 2);
}

TEST(AlgoIndexOfTests, InvalidIndex)
{
  int nums[4] = { 42, 123, 316, 1013 };
  autl::size_t idx = autl::IndexOf(nums, -100);
  EXPECT_EQ(idx, -1);

  // Only valid std container that passes ContiguousRange for the moment
  // std::ranges has a ContiguousRange concept that works via iterators that should probably be integrated
  std::initializer_list<int> nums2{ 42, 123, 316, 1013 };
  autl::size_t idx2 = autl::IndexOf(nums2, -100);
  EXPECT_EQ(idx, -1);
}

TEST(AlgoIndexOfTests, ValidIndexProjection)
{
  int nums[4] = { 42, 123, 316, 1013 };
  autl::size_t idx = autl::IndexOf(nums, 316);
  EXPECT_EQ(idx, 2);

  // Only valid std container that passes ContiguousRange for the moment
  // std::ranges has a ContiguousRange concept that works via iterators that should probably be integrated
  std::initializer_list<int> nums2{ 42, 123, 316, 1013 };
  autl::size_t idx2 = autl::IndexOf(nums2, 316);
  EXPECT_EQ(idx, 2);
}

TEST(AlgoIndexOfTests, InvalidIndexProjection)
{
  int nums[4] = { 42, 123, 316, 1013 };
  autl::size_t idx = autl::IndexOf(nums, -100);
  EXPECT_EQ(idx, -1);

  // Only valid std container that passes ContiguousRange for the moment
  // std::ranges has a ContiguousRange concept that works via iterators that should probably be integrated
  std::initializer_list<int> nums2{ 42, 123, 316, 1013 };
  autl::size_t idx2 = autl::IndexOf(nums2, -100);
  EXPECT_EQ(idx, -1);
}

TEST(AlgoIndexOfTests, ValidIndexByPredicate)
{
  auto pred = [](const int element) { return element % 2 != 0; }; // First odd

  int nums[4] = { 42, 123, 316, 1013 };
  autl::size_t idx = autl::IndexOfByPredicate(nums, pred);
  EXPECT_EQ(idx, 1);

  // Only valid std container that passes ContiguousRange for the moment
  // std::ranges has a ContiguousRange concept that works via iterators that should probably be integrated
  std::initializer_list<int> nums2{ 42, 123, 316, 1013 };
  autl::size_t idx2 = autl::IndexOfByPredicate(nums2, pred);
  EXPECT_EQ(idx, 1);
}

TEST(AlgoIndexOfTests, InvalidIndexByPredicate)
{
  auto pred = [](const int element) { return element == 0; };

  int nums[4] = { 42, 123, 316, 1013 };
  autl::size_t idx = autl::IndexOfByPredicate(nums, pred);
  EXPECT_EQ(idx, -1);

  // Only valid std container that passes ContiguousRange for the moment
  // std::ranges has a ContiguousRange concept that works via iterators that should probably be integrated
  std::initializer_list<int> nums2{ 42, 123, 316, 1013 };
  autl::size_t idx2 = autl::IndexOfByPredicate(nums2, pred);
  EXPECT_EQ(idx, -1);
}

#include "pch.h"

import autl.functional;

bool TestFunc0() { return true; }
bool TestFunc1(bool in) { return !in; }

TEST(FunctionalTests, InvokeFuncBasic)
{
  EXPECT_TRUE(autl::Invoke(TestFunc0));

  EXPECT_FALSE(autl::Invoke(TestFunc1, true));
}

TEST(FunctionalTests, Invoke_rFuncBasic)
{
  EXPECT_TRUE(autl::Invoke_r<bool>(TestFunc0));

  EXPECT_FALSE(autl::Invoke_r<bool>(TestFunc1, true));
}

TEST(FunctionalTests, InvokeLambdaBasic)
{
  auto test0 = []() -> bool { return true; };
  EXPECT_TRUE(autl::Invoke(test0));
  
  auto test1 = [](bool in) -> bool { return !in; };
  EXPECT_FALSE(autl::Invoke(test1, true));
}

class B
{
public:
  bool MyFunc()
  {
    return true;
  }

  bool MyOtherFunc(bool in)
  {
    return !in;
  }
};

TEST(FunctionalTests, InvokeMemberBasic)
{
  class A
  {
  public:
    bool MyFunc()
    {
      return true;
    }

    bool MyOtherFunc(bool in)
    {
      return !in;
    }
  };

  A a;
  EXPECT_TRUE(autl::Invoke(&A::MyFunc, a));

  EXPECT_FALSE(autl::Invoke(&A::MyOtherFunc, a, true));

  B b;
  EXPECT_TRUE(autl::Invoke(&B::MyFunc, b));

  EXPECT_FALSE(autl::Invoke(&B::MyOtherFunc, b, true));
}

TEST(FunctionalOperatorTests, InvokeIdentity)
{
  EXPECT_EQ(autl::Invoke(autl::Identity(), 1), 1);
}

TEST(FunctionalOperatorTests, InvokeLess)
{
  EXPECT_TRUE(autl::Invoke(autl::Less(), 1, 2));
}

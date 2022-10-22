#include "pch.h"

// Doesn't help
//#if __INTELLISENSE__
//#include "../ActuallyUseful/Modules/TypeTraits/TypeTraits.ixx"
//#include "../ActuallyUseful/Modules/Types/Types.ixx"
//#include "../ActuallyUseful/Modules/Utility/Utility.ixx"
//#else
import autl.type_traits;
import autl.types;
import autl.utility;
//#endif

TEST(TypeTraitsTests, IntegralConstant)
{
  using int0 = autl::IntergralConstant<int, 0>;
  EXPECT_EQ(int0::Value, 0);
  EXPECT_EQ(int0(), 0);
  EXPECT_NE(int0::Value, 1);
  EXPECT_NE(int0(), 1);

  using float0 = autl::IntergralConstant<float, 0.f>;
  EXPECT_FLOAT_EQ(float0::Value, 0.f);
  EXPECT_FLOAT_EQ(float0(), 0.f);
  EXPECT_FALSE(float0::Value == 1.f);
  EXPECT_FALSE(float0() == 1.f);
}

TEST(TypeTraitsTests, BoolConstant)
{
  EXPECT_EQ(autl::TrueType(), true);
  EXPECT_EQ(autl::TrueType::Value, true);
  EXPECT_EQ(autl::FalseType(), false);
  EXPECT_EQ(autl::FalseType::Value, false);
}

TEST(TypeTraitsTests, IsSame)
{
  using intSame = autl::IsSame<int, int>;
  EXPECT_TRUE(intSame::Value);
  constexpr bool intSameV = autl::IsSame_v<int, int>;
  EXPECT_TRUE(intSameV);

  using floatSame = autl::IsSame<float, float>;
  EXPECT_TRUE(floatSame::Value);
  constexpr bool floatSameV = autl::IsSame_v<float, float>;
  EXPECT_TRUE(floatSameV);

  using doubleSame = autl::IsSame<double, double>;
  EXPECT_TRUE(doubleSame::Value);
  constexpr bool doubleSameV = autl::IsSame_v<double, double>;
  EXPECT_TRUE(doubleSameV);

  using boolSame = autl::IsSame<bool, bool>;
  EXPECT_TRUE(boolSame::Value);
  constexpr bool boolSameV = autl::IsSame_v<bool, bool>;
  EXPECT_TRUE(boolSameV);

  using boolFloatSame = autl::IsSame<bool, float>;
  EXPECT_FALSE(boolFloatSame::Value);
  constexpr bool boolFloatSameV = autl::IsSame_v<bool, float>;
  EXPECT_FALSE(boolFloatSameV);
}

TEST(TypeTraitsTests, IsDifferent)
{
  using intCharDifferent = autl::IsDifferent<int, char>;
  EXPECT_TRUE(intCharDifferent::Value);
  constexpr bool intCharDifferentV = autl::IsDifferent_v<int, char>;
  EXPECT_TRUE(intCharDifferentV);
}

TEST(TypeTraitsTests, IsVoid)
{
  EXPECT_TRUE(autl::IsVoid<void>::Value);
  EXPECT_TRUE(autl::IsVoid_v<void>);
  EXPECT_FALSE(autl::IsVoid<int>::Value);
  EXPECT_FALSE(autl::IsVoid_v<int>);
  EXPECT_FALSE(autl::IsVoid<float>::Value);
  EXPECT_FALSE(autl::IsVoid_v<float>);
  EXPECT_FALSE(autl::IsVoid<double>::Value);
  EXPECT_FALSE(autl::IsVoid_v<double>);
  EXPECT_FALSE(autl::IsVoid<bool>::Value);
  EXPECT_FALSE(autl::IsVoid_v<bool>);
}

TEST(TypeTraitsTests, Conditional)
{
  using condition0_t = autl::Conditional_t<true, int, float>;
  constexpr bool cond0_same = autl::IsSame_v<int, condition0_t>;
  EXPECT_TRUE(cond0_same);

  using condition1_t = autl::Conditional_t<false, double, char>;
  constexpr bool cond1_same = autl::IsSame_v<char, condition1_t>;
  EXPECT_TRUE(cond1_same);
}

TEST(TypeTraitsTests, Disjunction)
{
  constexpr bool isBool = autl::Disjunction_v<autl::IsSame<bool, bool>>;
  EXPECT_TRUE(isBool);

  constexpr bool isInt = autl::Disjunction_v<autl::IsSame<int, bool>, autl::IsSame<int, int>>;
  EXPECT_TRUE(isInt);

  // Test aliases
  constexpr bool isBool2 = autl::OR_v<autl::IsSame<bool, bool>>;
  EXPECT_TRUE(isBool);

  constexpr bool isInt2 = autl::OR_v<autl::IsSame<int, bool>, autl::IsSame<int, int>>;
  EXPECT_TRUE(isInt);
}

TEST(TypeTraitsTests, Conjunction)
{
  constexpr bool noneBool = autl::Conjunction_v<autl::IsDifferent<bool,int>, autl::IsDifferent<bool, char>, autl::IsDifferent<bool, long long>, autl::IsDifferent<bool, float>>;
  EXPECT_TRUE(noneBool);

  constexpr bool falseNoneBool = autl::Conjunction_v<autl::IsDifferent<bool, int>, autl::IsDifferent<bool, char>, autl::IsDifferent<bool, bool>, autl::IsDifferent<bool, float>>;
  EXPECT_FALSE(falseNoneBool);

  // Test aliases
  constexpr bool noneBool2 = autl::AND_v<autl::IsDifferent<bool, int>, autl::IsDifferent<bool, char>, autl::IsDifferent<bool, long long>, autl::IsDifferent<bool, float>>;
  EXPECT_TRUE(noneBool);

  constexpr bool falseNoneBool2 = autl::AND_v<autl::IsDifferent<bool, int>, autl::IsDifferent<bool, char>, autl::IsDifferent<bool, bool>, autl::IsDifferent<bool, float>>;
  EXPECT_FALSE(falseNoneBool);
}

TEST(TypeTraitsTests, Negation)
{
  using trueThing = autl::IsSame<float, float>;
  constexpr bool negTrueThing = autl::Negation_v<trueThing>;
  EXPECT_FALSE(negTrueThing);

  using falseThing = autl::IsSame<float, double>;
  constexpr bool negFalseThing = autl::Negation_v<falseThing>;
  EXPECT_TRUE(negFalseThing);

  // Test aliases
  constexpr bool negTrueThing2 = autl::NOT_v<trueThing>;
  EXPECT_FALSE(negTrueThing);

  constexpr bool negFalseThing2 = autl::NOT_v<falseThing>;
  EXPECT_TRUE(negFalseThing);
}

TEST(TypeTraitsTests, IsAnyOf)
{
  constexpr bool isAnyOf0 = autl::IsAnyOf_v<bool, bool>;
  EXPECT_TRUE(isAnyOf0);
  constexpr bool isAnyOf1 = autl::IsAnyOf_v<bool, char>;
  EXPECT_FALSE(isAnyOf1);
  constexpr bool isAnyOf2 = autl::IsAnyOf_v<char, int, char, short>;
  EXPECT_TRUE(isAnyOf2);

  // Basically IsIntegral without the underlying BoolConstant
  constexpr bool isAnyOf3 = autl::IsAnyOf_v<autl::RemoveCV_t<unsigned long long>, bool
    , char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t
    , short, unsigned short
    , int, unsigned int
    , long, unsigned long
    , long long, unsigned long long>;
  EXPECT_TRUE(isAnyOf3);
}

TEST(TypeTraitsTests, IsIntegral)
{
  EXPECT_TRUE(autl::IsIntegral_v<bool>);
  EXPECT_TRUE(autl::IsIntegral_v<char>);
  EXPECT_TRUE(autl::IsIntegral_v<signed char>);
  EXPECT_TRUE(autl::IsIntegral_v<unsigned char>);
  EXPECT_TRUE(autl::IsIntegral_v<wchar_t>);
  EXPECT_TRUE(autl::IsIntegral_v<char8_t>);
  EXPECT_TRUE(autl::IsIntegral_v<char16_t>);
  EXPECT_TRUE(autl::IsIntegral_v<char32_t>);
  EXPECT_TRUE(autl::IsIntegral_v<short>);
  EXPECT_TRUE(autl::IsIntegral_v<unsigned short>);
  EXPECT_TRUE(autl::IsIntegral_v<int>);
  EXPECT_TRUE(autl::IsIntegral_v<unsigned int>);
  EXPECT_TRUE(autl::IsIntegral_v<long>);
  EXPECT_TRUE(autl::IsIntegral_v<unsigned long>);
  EXPECT_TRUE(autl::IsIntegral_v<long long>);
  EXPECT_TRUE(autl::IsIntegral_v<unsigned long long>);

  EXPECT_FALSE(autl::IsIntegral_v<float>);
  EXPECT_FALSE(autl::IsIntegral_v<double>);
  EXPECT_FALSE(autl::IsIntegral_v<long double>);

  EXPECT_FALSE(autl::IsIntegral_v<autl::nullptr_t>);
  EXPECT_FALSE(autl::IsIntegral_v<autl::byte>);
}

TEST(TypeTraitsTests, IsFloatingPoint)
{
  EXPECT_FALSE(autl::IsFloatingPoint_v<bool>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<char>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<signed char>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<unsigned char>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<wchar_t>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<char8_t>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<char16_t>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<char32_t>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<short>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<unsigned short>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<int>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<unsigned int>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<long>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<unsigned long>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<long long>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<unsigned long long>);

  EXPECT_TRUE(autl::IsFloatingPoint_v<float>);
  EXPECT_TRUE(autl::IsFloatingPoint_v<double>);
  EXPECT_TRUE(autl::IsFloatingPoint_v<long double>);

  EXPECT_FALSE(autl::IsFloatingPoint_v<autl::nullptr_t>);
  EXPECT_FALSE(autl::IsFloatingPoint_v<autl::byte>);
}

TEST(TypeTraitsTests, IsArithmetic)
{
  EXPECT_TRUE(autl::IsArithmetic_v<bool>);
  EXPECT_TRUE(autl::IsArithmetic_v<char>);
  EXPECT_TRUE(autl::IsArithmetic_v<signed char>);
  EXPECT_TRUE(autl::IsArithmetic_v<unsigned char>);
  EXPECT_TRUE(autl::IsArithmetic_v<wchar_t>);
  EXPECT_TRUE(autl::IsArithmetic_v<char8_t>);
  EXPECT_TRUE(autl::IsArithmetic_v<char16_t>);
  EXPECT_TRUE(autl::IsArithmetic_v<char32_t>);
  EXPECT_TRUE(autl::IsArithmetic_v<short>);
  EXPECT_TRUE(autl::IsArithmetic_v<unsigned short>);
  EXPECT_TRUE(autl::IsArithmetic_v<int>);
  EXPECT_TRUE(autl::IsArithmetic_v<unsigned int>);
  EXPECT_TRUE(autl::IsArithmetic_v<long>);
  EXPECT_TRUE(autl::IsArithmetic_v<unsigned long>);
  EXPECT_TRUE(autl::IsArithmetic_v<long long>);
  EXPECT_TRUE(autl::IsArithmetic_v<unsigned long long>);

  EXPECT_TRUE(autl::IsArithmetic_v<float>);
  EXPECT_TRUE(autl::IsArithmetic_v<double>);
  EXPECT_TRUE(autl::IsArithmetic_v<long double>);

  EXPECT_FALSE(autl::IsArithmetic_v<autl::nullptr_t>);
  EXPECT_FALSE(autl::IsArithmetic_v<autl::byte>);
}

TEST(TypeTraitsTests, IsSigned)
{
  EXPECT_TRUE(autl::IsSigned_v<float>);
  EXPECT_TRUE(autl::IsSigned_v<double>);
  EXPECT_TRUE(autl::IsSigned_v<char>);
  EXPECT_TRUE(autl::IsSigned_v<short>);
  EXPECT_TRUE(autl::IsSigned_v<int>);
  EXPECT_TRUE(autl::IsSigned_v<long long>);

  EXPECT_FALSE(autl::IsSigned_v<bool>);
  EXPECT_FALSE(autl::IsSigned_v<unsigned char>);
  EXPECT_FALSE(autl::IsSigned_v<unsigned short>);
  EXPECT_FALSE(autl::IsSigned_v<unsigned int>);
  EXPECT_FALSE(autl::IsSigned_v<unsigned long long>);
}

TEST(TypeTraitsTests, IsUnsigned)
{
  EXPECT_FALSE(autl::IsUnsigned_v<float>);
  EXPECT_FALSE(autl::IsUnsigned_v<double>);
  EXPECT_FALSE(autl::IsUnsigned_v<char>);
  EXPECT_FALSE(autl::IsUnsigned_v<short>);
  EXPECT_FALSE(autl::IsUnsigned_v<int>);
  EXPECT_FALSE(autl::IsUnsigned_v<long long>);

  EXPECT_TRUE(autl::IsUnsigned_v<bool>);
  EXPECT_TRUE(autl::IsUnsigned_v<unsigned char>);
  EXPECT_TRUE(autl::IsUnsigned_v<unsigned short>);
  EXPECT_TRUE(autl::IsUnsigned_v<unsigned int>);
  EXPECT_TRUE(autl::IsUnsigned_v<unsigned long long>);
}

TEST(TypeTraitsTests, RemoveRef)
{
  using RefType = bool&;
  using RemovedRefType = autl::RemoveReference_t<RefType>;
  constexpr bool isSame = autl::IsSame_v<bool, RemovedRefType>;
  EXPECT_TRUE(isSame);
}

TEST(TypeTraitsTests, RemoveConst)
{
  using ConstType = const bool;
  using RemovedConstType = autl::RemoveConst_t<ConstType>;
  constexpr bool isSame = autl::IsSame_v<bool, RemovedConstType>;
  EXPECT_TRUE(isSame);
}

TEST(TypeTraitsTests, RemoveVolatile)
{
  using VolatileType = volatile bool;
  using RemovedVolatileType = autl::RemoveVolatile_t<VolatileType>;
  constexpr bool isSame = autl::IsSame_v<bool, RemovedVolatileType>;
  EXPECT_TRUE(isSame);
}

TEST(TypeTraitsTests, RemoveCV)
{
  using ConstVolatileType = const volatile bool;
  using RemovedConstVolatileType = autl::RemoveCV_t<ConstVolatileType>;
  constexpr bool isSame = autl::IsSame_v<bool, RemovedConstVolatileType>;
  EXPECT_TRUE(isSame);
}

TEST(TypeTraitsTests, RemoveCVRef)
{
  using ConstVolatileRefType = const volatile bool&;
  using RemovedConstVolatileRefType = autl::RemoveCVRef_t<ConstVolatileRefType>;
  constexpr bool isSame = autl::IsSame_v<bool, RemovedConstVolatileRefType>;
  EXPECT_TRUE(isSame);
}

int f();
template<typename> struct pm_t {};
template<typename T, typename U> struct pm_t<T U::*>
{
  using Type = T;
};

TEST(TypeTraitsTests, IsFunction)
{
  struct A { int func(); };

  EXPECT_FALSE(autl::IsFunction_v<A>);
  EXPECT_TRUE(autl::IsFunction_v<int(int)>);
  EXPECT_TRUE(autl::IsFunction_v<decltype(f)>);
  EXPECT_FALSE(autl::IsFunction_v<int>);

  using T = pm_t<decltype(&A::func)>::Type;
  EXPECT_TRUE(autl::IsFunction_v<T>);
}

auto invocableDummy(char) -> int (*)()
{
  return nullptr;
}

auto noThrowDummy(char) noexcept -> int(*)()
{
  return nullptr;
}

struct P {};
auto noThrowDummy2(P, char) noexcept -> int(*)()
{
  return nullptr;
}

TEST(TypeTraitsTests, IsInvocable)
{
  EXPECT_TRUE(autl::IsInvocable_v<int()>);
  constexpr bool test2 = autl::IsInvocable_v<int(), int>;
  EXPECT_FALSE(test2);
  constexpr bool test3 = autl::IsInvocable_r_v<int, int()>;
  EXPECT_TRUE(test3);
  constexpr bool test4 = autl::IsInvocable_r_v<int*, int()>;
  EXPECT_FALSE(test4);
  constexpr bool test5 = autl::IsInvocable_r_v<void, void(int), int>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsInvocable_r_v<void, void(int), void>;
  EXPECT_FALSE(test6);
  constexpr bool test7 = autl::IsInvocable_r_v<int(*)(), decltype(invocableDummy), char>;
  EXPECT_TRUE(test7);
  constexpr bool test8 = autl::IsInvocable_r_v<int(*)(), decltype(invocableDummy), void>;
  EXPECT_FALSE(test8);
  constexpr bool test9 = autl::IsNoThrowInvocable_v<decltype(noThrowDummy), char>;
  EXPECT_TRUE(test9);
  constexpr bool test10 = autl::IsNoThrowInvocable_v<decltype(noThrowDummy), void>;
  EXPECT_FALSE(test10);
  constexpr bool test11 = autl::IsNoThrowInvocable_r_v<int(*)(), decltype(noThrowDummy), char>;
  EXPECT_TRUE(test11);
  constexpr bool test12 = autl::IsNoThrowInvocable_r_v<float, decltype(noThrowDummy), char>;
  EXPECT_FALSE(test12);
  constexpr bool test13 = autl::IsNoThrowInvocable_r_v<int(*)(), decltype(noThrowDummy2), P>;
  EXPECT_FALSE(test13);
  constexpr bool test14 = autl::IsNoThrowInvocable_r_v<int(*)(), decltype(noThrowDummy2), char, P>;
  EXPECT_FALSE(test14);
}

TEST(TypeTraitsTests, MakeSigned)
{
  constexpr bool test1 = autl::IsSame_v<autl::MakeSigned<char>::Type, signed char>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsSame_v<autl::MakeSigned<const char>::Type, const signed char>;
  EXPECT_TRUE(test2);

  constexpr bool test3 = autl::IsSame_v<autl::MakeSigned<short>::Type, signed short>;
  EXPECT_TRUE(test3);
  constexpr bool test4 = autl::IsSame_v<autl::MakeSigned<const short>::Type, const signed short>;
  EXPECT_TRUE(test4);

  constexpr bool test5 = autl::IsSame_v<autl::MakeSigned<int>::Type, signed int>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsSame_v<autl::MakeSigned<const int>::Type, const signed int>;
  EXPECT_TRUE(test6);

  constexpr bool test7 = autl::IsSame_v<autl::MakeSigned<long long>::Type, signed long long>;
  EXPECT_TRUE(test7);
  constexpr bool test8 = autl::IsSame_v<autl::MakeSigned<const long long>::Type, const signed long long>;
  EXPECT_TRUE(test8);
}

TEST(TypeTraitsTests, MakeUnsigned)
{
  constexpr bool test1 = autl::IsSame_v<autl::MakeUnsigned<char>::Type, unsigned char>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsSame_v<autl::MakeUnsigned<const char>::Type, const unsigned char>;
  EXPECT_TRUE(test2);

  constexpr bool test3 = autl::IsSame_v<autl::MakeUnsigned<short>::Type, unsigned short>;
  EXPECT_TRUE(test3);
  constexpr bool test4 = autl::IsSame_v<autl::MakeUnsigned<const short>::Type, const unsigned short>;
  EXPECT_TRUE(test4);

  constexpr bool test5 = autl::IsSame_v<autl::MakeUnsigned<int>::Type, unsigned int>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsSame_v<autl::MakeUnsigned<const int>::Type, const unsigned int>;
  EXPECT_TRUE(test6);

  constexpr bool test7 = autl::IsSame_v<autl::MakeUnsigned<long long>::Type, unsigned long long>;
  EXPECT_TRUE(test7);
  constexpr bool test8 = autl::IsSame_v<autl::MakeUnsigned<const long long>::Type, const unsigned long long>;
  EXPECT_TRUE(test8);
}

TEST(TypeTraitsTests, Constructible)
{
  class Foo
  {
    int v1;
    double v2;
  public:
    Foo(int n) : v1(n), v2() {}
    Foo(int n, double f) noexcept : v1(n), v2(f) {}
  };

  constexpr bool test1 = autl::IsConstructible_v<Foo, int>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsConstructible_v<Foo, int, double>;
  EXPECT_TRUE(test2);
  constexpr bool test3 = autl::IsConstructible_v<Foo, int, Foo>;
  EXPECT_FALSE(test3);

  constexpr bool test4 = autl::IsTriviallyConstructible_v<Foo, int>;
  EXPECT_FALSE(test4);
  constexpr bool test5 = autl::IsTriviallyConstructible_v<Foo, int, double>;
  EXPECT_FALSE(test5);
  constexpr bool test6 = autl::IsTriviallyConstructible_v<Foo, const Foo&>;
  EXPECT_TRUE(test6);

  constexpr bool test7 = autl::IsNoThrowConstructible_v<Foo, int>;
  EXPECT_FALSE(test7);
  constexpr bool test8 = autl::IsNoThrowConstructible_v<Foo, int, double>;
  EXPECT_TRUE(test8);
  constexpr bool test9 = autl::IsNoThrowConstructible_v<Foo, const Foo&>;
  EXPECT_TRUE(test9);

}

TEST(TypeTraitsTests, DefaultConstructible)
{
  class Foo
  {
    int i;
  public:
    // Non-trivial constructor, potentially throwing
    Foo(int a) : i(a) {}
    // No default constructor
    Foo() = delete;
  };

  class Bar
  {
    int i;
  public:
    // Trivial, noexcept, default constructible
    Bar() = default;
  };

  struct Baz
  {
    // Non-trivial member
    Foo foo;
  };

  constexpr bool test1 = autl::IsDefaultConstructible_v<Foo>;
  EXPECT_FALSE(test1);
  constexpr bool test2 = autl::IsDefaultConstructible_v<Bar>;
  EXPECT_TRUE(test2);
  constexpr bool test3 = autl::IsDefaultConstructible_v<Baz>;
  EXPECT_FALSE(test3);

  constexpr bool test4 = autl::IsTriviallyDefaultConstructible_v<Foo>;
  EXPECT_FALSE(test4);
  constexpr bool test5 = autl::IsTriviallyDefaultConstructible_v<Bar>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsTriviallyDefaultConstructible_v<Baz>;
  EXPECT_FALSE(test6);

  constexpr bool test7 = autl::IsNoThrowDefaultConstructible_v<Foo>;
  EXPECT_FALSE(test7);
  constexpr bool test8 = autl::IsNoThrowDefaultConstructible_v<Bar>;
  EXPECT_TRUE(test8);
  constexpr bool test9 = autl::IsNoThrowDefaultConstructible_v<Baz>;
  EXPECT_FALSE(test9);
}

TEST(TypeTraitsTests, CopyConstructible)
{
  class Foo
  {
    int i;
  public:
    // Non-trivial constructor, potentially throwing
    Foo(int a) : i(a) {}
    // No copy constructor
    Foo(const Foo&) = delete;
  };

  class Bar
  {
    int i;
  public:
    // Trivial, noexcept, default constructible
    Bar(const Bar&) = default;
  };

  struct Baz
  {
    // Non-trivial member
    Foo foo;
  };

  constexpr bool test1 = autl::IsCopyConstructible_v<Foo>;
  EXPECT_FALSE(test1);
  constexpr bool test2 = autl::IsCopyConstructible_v<Bar>;
  EXPECT_TRUE(test2);
  constexpr bool test3 = autl::IsCopyConstructible_v<Baz>;
  EXPECT_FALSE(test3);

  constexpr bool test4 = autl::IsTriviallyCopyConstructible_v<Foo>;
  EXPECT_FALSE(test4);
  constexpr bool test5 = autl::IsTriviallyCopyConstructible_v<Bar>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsTriviallyCopyConstructible_v<Baz>;
  EXPECT_FALSE(test6);

  constexpr bool test7 = autl::IsNoThrowCopyConstructible_v<Foo>;
  EXPECT_FALSE(test7);
  constexpr bool test8 = autl::IsNoThrowCopyConstructible_v<Bar>;
  EXPECT_TRUE(test8);
  constexpr bool test9 = autl::IsNoThrowCopyConstructible_v<Baz>;
  EXPECT_FALSE(test9);
}

TEST(TypeTraitsTests, MoveConstructible)
{
  class Foo
  {
    int i;
  public:
    // Non-trivial move constructor, potentially throwing
    Foo(Foo&& f) : i(f.i) {}
  };

  class Bar
  {
    int i;
  public:
    // Trivial, noexcept, default move constructible
    Bar(Bar&&) = default;
  };

  struct NoMove
  {
    // Define copy-constructor, preventing implicit declaration of nothrow default move constructor
    // Still Move Constructible due to copy-construct being able to bind to rvalue arg
    // Not trivial
    NoMove(const NoMove&) {}
  };

  struct TrueNoMove
  {
    // Delete both copy and move
    TrueNoMove(const TrueNoMove&) = delete;
    TrueNoMove(TrueNoMove&&) = delete;
  };

  constexpr bool test1 = autl::IsMoveConstructible_v<TrueNoMove>;
  EXPECT_FALSE(test1);
  constexpr bool test2 = autl::IsMoveConstructible_v<Bar>;
  EXPECT_TRUE(test2);
  constexpr bool test3 = autl::IsMoveConstructible_v<NoMove>;
  EXPECT_TRUE(test3);

  constexpr bool test4 = autl::IsTriviallyMoveConstructible_v<Foo>;
  EXPECT_FALSE(test4);
  constexpr bool test5 = autl::IsTriviallyMoveConstructible_v<Bar>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsTriviallyMoveConstructible_v<NoMove>;
  EXPECT_FALSE(test6);

  constexpr bool test7 = autl::IsNoThrowMoveConstructible_v<Foo>;
  EXPECT_FALSE(test7);
  constexpr bool test8 = autl::IsNoThrowMoveConstructible_v<Bar>;
  EXPECT_TRUE(test8);
  constexpr bool test9 = autl::IsNoThrowMoveConstructible_v<NoMove>;
  EXPECT_FALSE(test9);
}

TEST(TypeTraitsTests, IsTrivial)
{
  // Trivial
  struct A
  {
    int a;
  };

  // Not trivial
  struct B
  {
    B() {}
  };

  constexpr bool test1 = autl::IsTrivial_v<A>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsTrivial_v<B>;
  EXPECT_FALSE(test2);
}

TEST(TypeTraitsTests, IsStandardLayout)
{
  // Standard layout
  struct A
  {
    int a;
  };

  // Non-standard layouts
  struct B
  {
    int b1;
  private:
    int b2;
  };

  struct C
  {
    virtual void Foo() {}
  };

  constexpr bool test1 = autl::IsStandardLayout_v<A>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsStandardLayout_v<B>;
  EXPECT_FALSE(test2);
  constexpr bool test3 = autl::IsStandardLayout_v<C>;
  EXPECT_FALSE(test3);
}

TEST(TypeTraitsTests, IsAssignable)
{
  // Trivial
  struct A
  {
    int a;
  };

  // custom copy, no noexcept
  struct B
  {
    int b;
    B(const B& _b) { b = _b.b; }
    B(B&& _b) { b = _b.b; }
  };

  constexpr bool test1 = autl::IsAssignable_v<int, int>;
  EXPECT_FALSE(test1);
  constexpr bool test2 = autl::IsAssignable_v<int&, int>;
  EXPECT_TRUE(test2);
  constexpr bool test3 = autl::IsAssignable_v<int, double>;
  EXPECT_FALSE(test3);
  constexpr bool test4 = autl::IsAssignable_v<int&, double>;
  EXPECT_TRUE(test4);

  constexpr bool test5 = autl::IsTriviallyAssignable_v<A&, A>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsTriviallyAssignable_v<B&, B>;
  EXPECT_FALSE(test6);
  constexpr bool test7 = autl::IsNoThrowAssignable_v<A&, A>;
  EXPECT_TRUE(test7);
  constexpr bool test8 = autl::IsNoThrowAssignable_v<B&, B>;
  EXPECT_FALSE(test8);
}

TEST(TypeTraitsTests, IsCopyAssignable)
{
  // Trivial
  struct A
  {
    int a;
  };

  // non-trivial copy, no noexcept
  struct B
  {
    int b;
    B& operator=(const B& _b) { b = _b.b; }
  };

  // No-copy
  struct C
  {
    int c;
    C& operator=(const C& _c) = delete;
  };

  constexpr bool test1 = autl::IsCopyAssignable_v<A>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsCopyAssignable_v<C>;
  EXPECT_FALSE(test2);

  constexpr bool test3 = autl::IsTriviallyCopyAssignable_v<A>;
  EXPECT_TRUE(test3);
  constexpr bool test4 = autl::IsTriviallyCopyAssignable_v<B>;
  EXPECT_FALSE(test4);

  constexpr bool test5 = autl::IsNoThrowCopyAssignable_v<A>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsNoThrowCopyAssignable_v<B>;
  EXPECT_FALSE(test6);
}

TEST(TypeTraitsTests, IsMoveAssignable)
{
  // Trivial
  struct A
  {
    int a;
  };

  // non-trivial move assign, no noexcept
  struct B
  {
    int b;
    B& operator=(B&& _b) { b = _b.b; }
  };

  // Deleted move assign
  struct C
  {
    int c;
    C& operator=(C&& _c) = delete;
  };

  // nothrow
  struct D
  {
    int d;
    D& operator=(D&& _d) noexcept { d = _d.d; }
  };

  constexpr bool test1 = autl::IsMoveAssignable_v<A>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsMoveAssignable_v<B>;
  EXPECT_TRUE(test2);
  constexpr bool test3 = autl::IsMoveAssignable_v<C>;
  EXPECT_FALSE(test3);

  constexpr bool test4 = autl::IsTriviallyMoveAssignable_v<A>;
  EXPECT_TRUE(test4);
  constexpr bool test5 = autl::IsTriviallyMoveAssignable_v<B>;
  EXPECT_FALSE(test5);
  
  constexpr bool test6 = autl::IsNoThrowMoveAssignable_v<A>;
  EXPECT_TRUE(test6);
  constexpr bool test7 = autl::IsNoThrowMoveAssignable_v<B>;
  EXPECT_FALSE(test7);
  constexpr bool test8 = autl::IsNoThrowMoveAssignable_v<D>;
  EXPECT_TRUE(test8);
}

TEST(TypeTraitsTests, IsSwappable)
{
  // Swappable
  struct A
  {
    int a;
  };

  // Not swappable, no move constructor, no move assign
  struct B
  {
    int b;
    B& operator=(B&&) = delete;
    B(B&&) = delete;
  };

  constexpr bool test1 = autl::IsSwappable_v<A>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsSwappable_v<B>;
  EXPECT_FALSE(test2);

  constexpr bool test3 = autl::IsNoThrowSwappable_v<A>;
  EXPECT_TRUE(test3);
  constexpr bool test4 = autl::IsNoThrowSwappable_v<B>;
  EXPECT_FALSE(test4);

  constexpr bool test5 = autl::IsSwappableWith_v<int, int>;
  EXPECT_FALSE(test5);
  constexpr bool test6 = autl::IsSwappableWith_v<int&, int&>;
  EXPECT_TRUE(test6);

  constexpr bool test7 = autl::IsNoThrowSwappableWith_v<A&, A&>;
  EXPECT_TRUE(test7);
  constexpr bool test8 = autl::IsNoThrowSwappableWith_v<int&, int&>;
  EXPECT_TRUE(test8);
}

TEST(TypeTraitsTests, IsDestructible)
{
  // Destructible, nothrow, not trivial
  struct A
  {
    ~A() noexcept {}
  };

  // Destructible, nothrow, trivial
  struct B
  {
    ~B() = default;
  };

  // Deleted constructor, impossible to create but not UB
  struct C
  {
    ~C() = delete;
  };

  constexpr bool test1 = autl::IsDestructible_v<A>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::IsDestructible_v<B>;
  EXPECT_TRUE(test2);
  constexpr bool test3 = autl::IsDestructible_v<C>;
  EXPECT_FALSE(test3);

  constexpr bool test4 = autl::IsTriviallyDestructible_v<A>;
  EXPECT_FALSE(test4);
  constexpr bool test5 = autl::IsTriviallyDestructible_v<B>;
  EXPECT_TRUE(test5);
  constexpr bool test6 = autl::IsTriviallyDestructible_v<C>;
  EXPECT_FALSE(test6);

  constexpr bool test7 = autl::IsNoThrowDestructible_v<A>;
  EXPECT_TRUE(test7);
  constexpr bool test8 = autl::IsNoThrowDestructible_v<B>;
  EXPECT_TRUE(test8);
  constexpr bool test9 = autl::IsNoThrowDestructible_v<C>;
  EXPECT_FALSE(test9);
}

TEST(TypeTraitsTests, HasUniqueObjectRepresentations)
{
  // Should be unique due to no internal padding
  struct A
  {
    int a;
    int b;
  };

  // ints require 4-byte alignment therefore inserting 3 bytes of "nothing" between c and i invalidates
  // the value vs object equality
  struct B
  {
    char c;
    int i;
  };

  constexpr bool test1 = autl::HasUniqueObjectRepresentations_v<A>;
  EXPECT_TRUE(test1);
  constexpr bool test2 = autl::HasUniqueObjectRepresentations_v<B>;
  EXPECT_FALSE(test2);
}

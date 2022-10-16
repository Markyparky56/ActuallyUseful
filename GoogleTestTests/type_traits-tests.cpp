#include "pch.h"

import autl.type_traits;
import autl.types;
import autl.utility;

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
}

TEST(TypeTraitsTests, Conjunction)
{
  constexpr bool noneBool = autl::Conjunction_v<autl::IsDifferent<bool,int>, autl::IsDifferent<bool, char>, autl::IsDifferent<bool, long long>, autl::IsDifferent<bool, float>>;
  EXPECT_TRUE(noneBool);

  constexpr bool falseNoneBool = autl::Conjunction_v<autl::IsDifferent<bool, int>, autl::IsDifferent<bool, char>, autl::IsDifferent<bool, bool>, autl::IsDifferent<bool, float>>;
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

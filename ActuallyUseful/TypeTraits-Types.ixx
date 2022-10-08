module;
export module autl.type_traits.types;

import autl.type_traits.integralconstant;
import autl.type_traits.constvolatile;

/*
* ActuallyUseful Type Traits helpers
*/
export namespace autl
{
  /*
  * Provide type unmodified
  */
  template<typename T> struct TypeIdentity { using Type = T; };

  /*
  * void utility metafunction
  */
  template<typename...> using Void_t = void;

  /*
  * False value attached to a dependent name (for static_assert)
  * Non-standard, borrowed from MSVC STL
  */
  template<typename> inline constexpr bool AlwaysFalse = false;

  /*
  * Type conditional on first template param
  */
  template<bool B, typename TTrue, typename TFalse> struct Conditional { using Type = TTrue; };
  template<typename TTrue, typename TFalse> struct Conditional<false, TTrue, TFalse> { using Type = TFalse; };

  /*
  * Helper to access ::Type of Conditional
  */
  template<bool B, typename TTrue, typename TFalse> using Conditional_t = typename Conditional<B, TTrue, TFalse>::Type;

  /*
  * Logical disjunction (OR) of given types
  */
  template<typename...> struct Disjunction : FalseType {};
  template<typename B1> struct Disjunction<B1> : B1 {};
  template<typename B1, typename... Bn> struct Disjunction<B1, Bn...> 
    : Conditional_t<bool(B1::Value), B1, Disjunction<Bn...>> 
  {
    // If B1 is true, "return" true (inherit from and end recursion)
  };

  /*
  * Helper to access ::Value of Disjunction
  */
  template<typename... Bs> inline constexpr bool Disjunction_v = Disjunction<Bs...>::Value;

  /*
  * Logical AND of given types
  */
  template<typename...> struct Conjunction : TrueType {};
  template<typename B1> struct Conjunction<B1> : B1 {};
  template<typename B1, typename... Bn> struct Conjunction<B1, Bn...> 
    : Conditional_t<bool(B1::Value), Conjunction<Bn...>, B1>
  {
    // If B1 is false, "return" false (inherit from and end recursion)
  };

  /*
  * Helper to access ::Value of Conjunction
  */
  template<typename... Bs> inline constexpr bool Conjunction_v = Conjunction<Bs...>::Value;

  /*
  * Logical NOT of given Type::Value
  */
  template<typename B> struct Negation : BoolConstant<!bool(B::Value)> {};

  /*
  * Helper to access ::Value of Negation
  */
  template<typename B> inline constexpr bool Negation_v = Negation<B>::Value;

  /*
  * Provide constant integral value corresponding to if L & R are the same type
  */
  template<typename L, typename R> struct IsSame : FalseType {};
  template<typename T> struct IsSame<T, T> : TrueType {};

  /*
  * Helper to access ::Value of IsSame
  * Constant value corresponding to if L & R are the same type
  */
  template<typename L, typename R> inline constexpr bool IsSame_v = IsSame<L, R>::Value;

  /*
  * Provide constant integral value corresponding to if L & R are not the same type
  */
  template<typename L, typename R> struct IsDifferent : TrueType {};
  template<typename T> struct IsDifferent<T, T> : FalseType {};

  /*
  * Helper to access ::Value of IsDifferent
  * Constant value corresponding to if L & R are not the same type
  */
  template<typename L, typename R> inline constexpr bool IsDifferent_v = IsDifferent<L, R>::Value;

  /*
  * Checks whether T is a void type
  */
  template<typename T> struct IsVoid : IsSame<void, typename RemoveCV_t<T>> {};

  /*
  * Helper to access ::Value of IsVoid
  * Constant value corresponding to if T is a void type
  */
  template<typename T> inline constexpr bool IsVoid_v = IsVoid<T>::Value;

  /*
  * Helper to determine if given type T is in list Types
  */
  template<typename T, typename... Types> inline constexpr bool IsAnyOf_v = Disjunction_v<IsSame<T, Types>...>;

  /*
  * Is given type T any of the integral (int) types
  */
  template<typename T> struct IsIntegral
    : BoolConstant<IsAnyOf_v<RemoveCV_t<T>
    , bool
    , char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t
    , short, unsigned short
    , int, unsigned int
    , long, unsigned long
    , long long, unsigned long long>> {};

  /*
  * Helper to access ::Value of IsIntegral
  */
  template<typename T> inline constexpr bool IsIntegral_v = IsIntegral<T>::Value;

  /*
  * Is given type T any of the floating point types
  */
  template<typename T> struct IsFloatingPoint
    : BoolConstant<IsAnyOf_v<RemoveCV_t<T>
    , float
    , double, long double>> {};

  /*
  * Helper to access ::Value of IsFloatingPoint
  */
  template<typename T> inline constexpr bool IsFloatingPoint_v = IsFloatingPoint<T>::Value;

  /*
  * Is given type T arithmetic (integral of floating point)?
  */
  template<typename T> struct IsArithmetic : BoolConstant<IsIntegral_v<T> || IsFloatingPoint_v<T>> {};

  /*
  * Helper to access ::Value of IsArithmetic
  */
  template<typename T> inline constexpr bool IsArthimetic_v = IsArithmetic<T>::Value;

}
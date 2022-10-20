module;
export module autl.type_traits.logical;

import autl.type_traits.core;
import autl.type_traits.integralconstant;
import autl.type_traits.constvolatile;

/*
* ActuallyUseful Type Traits Logical Helpers
*/
export namespace autl
{
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
  * Logical disjunction (OR) of given input
  * Inputs must provide a public ::Value member
  * True if any ::Value members eval to true
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
  * Alias for "Disjunction"
  * Logical OR
  * Input must provide a public ::Value member
  * True if any ::Value members eval to true
  */
  template<typename... Bs> using OR = Disjunction<Bs...>;

  /*
  * Alias for "Disjunction_v"
  * Logical OR
  * Inputs must provide a public ::Value member
  * True if any ::Value members eval to true
  */
  template<typename... Bs> inline constexpr bool OR_v = OR<Bs...>::Value;

  /*
  * Logical AND of given inputs
  * Inputs must provide a public ::Value member
  * True if all ::Value members eval to true
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
  * Alis for "Conjunction"
  * Logical AND
  * Inputs must provide a public ::Value member
  * True if all ::Value members eval to true
  */
  template<typename... Bs> using AND = Conjunction<Bs...>;

  /*
  * Alis for "Conjunction_v"
  * Logical AND
  * Inputs must provide a public ::Value member
  * True if all ::Value members eval to true
  */
  template<typename... Bs> inline constexpr bool AND_v = AND<Bs...>::Value;

  /*
  * Logical NOT of given Type::Value
  * Input must provide a public ::Value member
  * Inverts input value
  */
  template<typename B> struct Negation : BoolConstant<!bool(B::Value)> {};

  /*
  * Helper to access ::Value of Negation
  */
  template<typename B> inline constexpr bool Negation_v = Negation<B>::Value;

  /*
  * Alias for Negation
  * Logical NOT
  * Input must provide a public ::Value member
  * Inverts input value
  */
  template<typename B> using NOT = Negation<B>;

  /*
  * Alias for Negation_v
  * Logical NOT
  * Input must provide a public ::Value member
  * Inverts input value
  */
  template<typename B> inline constexpr bool NOT_v = NOT<B>::Value;

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
  * Helper to determine if given type T is in list Types
  */
  template<typename T, typename... Types> inline constexpr bool IsAnyOf_v = Disjunction_v<IsSame<T, Types>...>;

  /*
  * Determine is type Base is derived from type Derived
  * (Uses builtin, cppreference has a meta-method)
  */
  template<typename Base, typename Derived> struct IsBaseOf : BoolConstant<__is_base_of(Base, Derived)> {};

  /*
  * Helper to access ::Value of IsBaseOf
  */
  template<typename Base, typename Derived> inline constexpr bool IsBaseOf_v = IsBaseOf<Base, Derived>::Value;
}
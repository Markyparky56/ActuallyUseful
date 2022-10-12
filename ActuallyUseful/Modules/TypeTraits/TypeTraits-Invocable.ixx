module;
#include "../Internal/Internal-Invoker.h"
export module autl.type_traits.invocable;

import autl.type_traits.core;
import autl.type_traits.integralconstant;
import autl.type_traits.logical;
import autl.type_traits.isvoid;
import autl.utility.declval;

// Helpers in the style of MSVC because it was the most legible and sane looking
// I've tried to improve on that legibility a tad.
namespace autl
{
  template<class T> T ReturnsExactly() noexcept; // undefined dummy func
  template<typename To> void ImplicitConvertTo(To) noexcept; // undefined dummy func

  template<typename From, typename To, class = void>
  struct InvokeConvertible : FalseType {};

  template<typename From, typename To>
  struct InvokeConvertible<From, To, Void_t<decltype(ImplicitConvertTo<To>(ReturnsExactly<From>()))>>
    : TrueType {};
  template<typename From, typename To>
  struct InvokeNoThrowConvertible
    : BoolConstant<noexcept(ImplicitConvertTo<To>(ReturnsExactly<From>()))> {};

  template<typename Result, bool NoThrow>
  struct InvokeTraitsCommon
  {
    using Type = Result;
    using IsInvocable = TrueType;
    using IsNoThrowInvocable = BoolConstant<NoThrow>;

    // True if either returns void, or Result matches Invocable result (r)
    template<typename R>
    using IsInvocable_r = BoolConstant<Disjunction_v<IsVoid<R>, InvokeConvertible<Type, R>>>;
    // True if...
    // IsNoThrowInvocable (NoThrow)
    // AND either returns void 
    //    OR Result is convertible to R AND is no throw on convert
    template<typename R>
    using IsNoThrowInvocable_r = BoolConstant<
      Conjunction_v<IsNoThrowInvocable,
        Disjunction<IsVoid<R>,
          Conjunction<InvokeConvertible<Type, R>, InvokeNoThrowConvertible<Type, R>>
        > // Disjunction
      > // Conjunction_v
    >; // BoolConstant
  };

  // Selected when Callable isn't callable with zero args
  template<typename Void, typename Callable>
  struct InvokeTraitsZero
  {
    using IsInvocable = FalseType;
    using IsNoThrowInvocable = FalseType;
    template<typename R> using IsInvocable_r = FalseType;
    template<typename R> using IsNoThrowInvocable_r = FalseType;
  };

  template<typename Callable> using DecltypeInvokeZero = decltype(Declval<Callable>()());

  template<typename Callable>
  struct InvokeTraitsZero<Void_t<DecltypeInvokeZero<Callable>>, Callable>
    : InvokeTraitsCommon<DecltypeInvokeZero<Callable>, noexcept(Declval<Callable>()())> {};

  // Selected when Callable isn't callable with nonzero args
  template<typename Void, typename... Types>
  struct InvokeTraitsNonZero
  {
    using IsInvocable = FalseType;
    using IsNoThrowInvocable = FalseType;
    template<typename R> using IsInvocable_r = FalseType;
    template<typename R> using IsNoThrowInvocable_r = FalseType;
  };

  template<typename Callable, typename T, typename... Ts>
  using DecltypeInvokeNonZero = decltype(Declval<Callable>()());

  template<typename Callable, typename T, typename... Ts>
  struct InvokeTraitsNonZero<Void_t<DecltypeInvokeNonZero<Callable, T, Ts...>>, Callable, T, Ts...>
    : InvokeTraitsCommon<DecltypeInvokeNonZero<Callable, T, Ts...>, noexcept(Invoker<Callable, T>::Call(Declval<Callable>(), Declval<T>(), Declval<Ts>()...))> {};

  template<typename Callable, typename... Args>
  using SelectInvokeTraits = Conditional_t<sizeof...(Args) == 0, InvokeTraitsZero<void, Callable>, InvokeTraitsNonZero<void, Callable, Args...>>;
}

export namespace autl
{
  /*
  * Deduce the return type of an invoke of given Callable at compile time
  */
  template<typename Callable, typename... Args>
  struct InvokeResult : SelectInvokeTraits<Callable, Args...> {};

  /*
  * Helper to access ::Type of InvokeResult
  */
  template<typename Callable, typename... Args>
  using InvokeResult_t = typename InvokeResult<Callable, Args...>::Type;

  /*
  * Determines if given Callable can be invoked with given arguments
  */
  template<typename Callable, typename... Args>
  struct IsInvocable : InvokeResult<Callable, Args...>::template IsInvocable {};

  /*
  * Helper to access ::Value of IsInvocable
  */
  template<typename Callable, typename... Args>
  inline constexpr bool IsInvocable_v = IsInvocable<Callable, Args...>::Value;

  /*
  * Determines if given Callable can be invoked with given arguments to yield a result that is convertible to type R
  */
  template<typename R, typename Callable, typename... Args>
  struct IsInvocable_r : InvokeResult<Callable, Args...>::template IsInvocable_r{};

  /*
  * Helper to access ::Value of IsInvocable_r
  */
  template<typename Callable, typename... Args>
  inline constexpr bool IsInvocable_r_v = IsInvocable_r<Callable, Args...>::Value;

  /*
  * Determines if given Callable can be invoked with given arguments and that the call is known to not throw any exceptions
  */
  template<typename Callable, typename... Args>
  struct IsNoThrowInvocable : InvokeResult<Callable, Args...>::template IsNoThrowInvocable{};

  /*
  * Helper to access ::Value of IsNoThrowInvocable
  */
  template<typename Callable, typename... Args>
  inline constexpr bool IsNoThrowInvocable_v = IsNoThrowInvocable<Callable, Args...>::Value;

  /*
  * Determines if given Callable:
  * - Can be invoked with given arguments
  * - Will yield a result that is convertible to type R
  * - Is known to not throw any exceptions
  */
  template<typename R, typename Callable, typename... Args>
  struct IsNoThrowInvocable_r : InvokeResult<Callable, Args...>::template IsNoThrowInvocable_r{};

  /*
  * Helper to access ::Value of IsNoThrowInvocable_r
  */
  template<typename Callable, typename... Args>
  inline constexpr bool IsNoThrowInvocable_r_v = IsNoThrowInvocable_r<Callable, Args...>::Value;
}

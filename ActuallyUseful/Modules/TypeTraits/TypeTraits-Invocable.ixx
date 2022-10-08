module;
export module autl.type_traits.invocable;

import autl.type_traits.core;
import autl.type_traits.integralconstant;
import autl.type_traits.logical;
import autl.utility.declval;

// Helpers in the style of MSVC because it was the most legible and sane looking
// I've tried to improve on that legibility a tad.
namespace autl
{
  //// Forward declare ReferenceWrapper and cross our fingers it works (templates do be magic)
  //template<typename T> class ReferenceWrapper;

  //// Assuming pmf is pointer-to-member-function
  //// and pmd is pointer-to-member-data?
  //enum class InvokerStrategy
  //{
  //  Functor,
  //  PMF_Object,
  //  PMF_Refwrap,
  //  PMF_Pointer,
  //  PMD_Object,
  //  PMD_Refwrap,
  //  PMD_Pointer
  //};

  //struct InvokerFunctor
  //{
  //  static constexpr InvokerStrategy Strategy = InvokerStrategy::Functor;

  //  template<typename Callable, typename... Ts>
  //  static constexpr auto Call(Callable&& obj, Ts&&... args) noexcept(noexcept(static_cast<Callable&&>(obj)(static_cast<Ts&&>(args)...)))
  //    -> decltype(static_cast<Callable&&>(obj)(static_cast<Ts&&>(args)...))
  //  {
  //    return static_cast<Callable&&>(obj)(static_cast<Ts&&>(args)...);
  //  }
  //};

  //struct InvokerPMFObject
  //{
  //  static constexpr InvokerStrategy Strategy = InvokerStrategy::PMF_Object;

  //  template<typename Decayed, typename T, typename... Ts>
  //  static constexpr auto Call(Decayed pmf, T&& arg1, Ts&&... args) noexcept(noexcept((static_cast<T&&>(arg1).*pmf)(static_cast<Ts&&>(args)...)))
  //    -> decltype((static_cast<T&&>(arg1).*pmf)(static_cast<Ts&&>(args)...))
  //  {
  //    return (static_cast<T&&>(arg1).*pmf)(static_cast<Ts&&>(args)...);
  //  }
  //};

  //struct InvokerPMFRefwrap
  //{
  //  static constexpr InvokerStrategy Strategy = InvokerStrategy::PMD_Refwrap;

  //  template<typename Decayed, typename Refwrap, typename... Ts>
  //  static constexpr auto Call(Decayed pmf, Refwrap rw, Ts&&... args) noexcept(noexcept((rw.Get().*pmf)(static_cast<Ts&&>(args)...)))
  //    -> decltype((rw.Get().*pmf)(static_cast<Ts&&>(args)...))
  //  {
  //    return (rw.Get().*pmf)(static_cast<Ts&&>(args)...);
  //  }
  //};

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
  struct InvokeTraitsNonzero
  {
    using IsInvocable = FalseType;
    using IsNoThrowInvocable = FalseType;
    template<typename R> using IsInvocable_r = FalseType;
    template<typename R> using IsNoThrowInvocable_r = FalseType;
  };

  //template<typename Callable, typename T, typename... Ts>
  //using DecltypeInvokeNonzero = decltype()
}

export namespace autl
{
  /*
  * Determines if given Fn can be invoked with given arguments
  */
  //template<typename Fn, typename... ArgTypes> struct IsInvocable
}

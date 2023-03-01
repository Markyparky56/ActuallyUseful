module;
export module autl.type_traits.commontype;

import autl.type_traits.logical;
import autl.type_traits.core;
import autl.type_traits.removecvref;
import autl.type_traits.isvoid;
import autl.type_traits.decay;
import autl.utility.declval;

export namespace autl
{
  /*
  * Determines the common type among all types T..., allowing for implicit conversion if such a type exists
  * Common type exposed as member ::Type if such a type exists, otherwise there is no member ::Type
  */
  template<typename... Ts> struct CommonType;
  template<> struct CommonType<> {}; // No common type

  /*
  * Helper to access ::Type of CommonType
  */
  template<typename... Ts> using CommonType_t = typename CommonType<Ts...>::Type;
}

// Un-exported helpers
namespace autl
{
  template<typename T, typename U> using CondType = decltype(false ? Declval<T>() : Declval<U>());

  // Setup for decay
  template<typename T, typename U, class = void> struct ConstLValueCondOper {};
  template<typename T, typename U> struct ConstLValueCondOper<T, U, Void_t<CondType<const T&, const U&>>>
  {
    using Type = RemoveCVRef_t<CondType<const T&, const U&>>;
  };
  // Decay condition
  template<typename T, typename U, class = void> struct DecayedCondOper : ConstLValueCondOper<T, U> {};
  template<typename T, typename U> struct DecayedCondOper<T, U, Void_t<CondType<T, U>>>
  {
    using Type = Decay_t<CondType<T, U>>;
  };

  // Two-type helpers
  template<typename T, typename U, typename TDecayed = Decay_t<T>, typename UDecayed = Decay_t<U>>
  struct CommonType2 : CommonType<TDecayed, UDecayed> {};
  template<typename T, typename U>
  struct CommonType2<T, U, T, U> : DecayedCondOper<T, U> {};

  // Three-type helpers
  template<typename Void, typename T, typename U, typename... Rest>
  struct CommonType3 {};
  template<typename T, typename U, typename... Rest>
  struct CommonType3<Void_t<CommonType_t<T, U>>, T, U, Rest...> : CommonType<CommonType_t<T, U>, Rest...> {};
}

export namespace autl
{
  // The real implementations

  template<typename T> struct CommonType<T> : CommonType<T, T> {};
  template<typename T, typename U> struct CommonType<T, U> : CommonType2<T, U> {};
  template<typename T, typename U, typename... Rest> struct CommonType<T, U, Rest...> : CommonType3<void, T, U, Rest...> {};
}

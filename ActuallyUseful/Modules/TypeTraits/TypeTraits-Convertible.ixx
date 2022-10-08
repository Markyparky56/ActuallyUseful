module;
export module autl.type_traits.convertible;

import autl.utility.declval;
import autl.type_traits.integralconstant;
import autl.type_traits.logical;

export namespace autl
{
  // Use builtins, fail-out if unavailable
  // MSVC, GCC, & Clang all have their own.
  // Re-evaluate your life choices if you ever find another you need to support
#undef IS_CONVERTIBLE_TO
#if defined(_MSC_VER) || defined(__clang__)
#define IS_CONVERTIBLE_TO __is_convertible_to
#else
#define IS_CONVERTIBLE_TO __is_convertible
#endif
  /*
  * Tests if From can be implicitly converted to To
  */
  template<typename From, typename To> struct IsConvertible 
    : BoolConstant<IS_CONVERTIBLE_TO(From, To)> {};
#undef IS_CONVERTIBLE_TO

  /*
  * Helper to access ::Value of IsConvertible
  */
  template<typename From, typename To> inline constexpr bool IsConvertible_v = IsConvertible<From, To>::Value;
}

// nothrow helpers, largely in the sytle of MSVC since it had the least boilerplate for once
namespace autl
{
  template<typename To> void ImplicitConvertTo(To) noexcept; // undefined dummy func

  template<typename From, typename To, bool = IsConvertible_v<From, To>, bool = IsVoid_v<To>>
  inline constexpr bool IsNoThrowConvertibleHelper_v = noexcept(ImplicitlConvertTo<To>(Declval<From>()));

  template<typename From, typename To, bool _IsVoid>
  inline constexpr bool IsNoThrowConvertibleHelper_v<From, To, false, _IsVoid> = false;

  template<typename From, typename To>
  inline constexpr bool IsNoThrowConvertibleHelper_v<From, To, true, true> = true;
}

export namespace autl
{
  /*
  * Tests if From can be implicitly converted to To with no risk of throwing
  */
  template<typename From, typename To> 
  struct IsNoThrowConvertible : BoolConstant<IsNoThrowConvertibleHelper_v<From, To>> {};

  /*
  * Helper to access ::Value of IsNoThrowConvertible
  */
  template<typename From, typename To> inline constexpr bool IsNoThrowConvertible_v = IsNoThrowConvertible<From, To>::Value;
}

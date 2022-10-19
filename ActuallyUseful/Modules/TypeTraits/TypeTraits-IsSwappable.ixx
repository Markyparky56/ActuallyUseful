module;
export module autl.type_traits.isswappable;

import autl.utility.declval;
import autl.type_traits.isconstructible;
import autl.type_traits.isassignable;
import autl.type_traits.enableif;
import autl.type_traits.integralconstant;
import autl.type_traits.isvoid;
import autl.type_traits.logical;
import autl.type_traits.reference;

namespace autl
{
  // Forward declare IsSwappable and IsNoThrowSwappable
  template<typename T> struct IsSwappable;
  template<typename T> struct IsNoThrowSwappable;

  // Forward declare swap for Declval
  template<typename T, EnableIf_t<IsMoveConstructible_v<T> && IsMoveAssignable_v<T>, int> = 0>
  constexpr void Swap(T& a, T& b) noexcept(IsNoThrowMoveConstructible_v<T>&& IsNoThrowMoveAssignable_v<T>);
  template<typename T, size_t N, EnableIf_t<IsSwappable<T>::Value, int> = 0>
  constexpr void Swap(T (&left)[N], T (&right)[N]) noexcept(IsNoThrowSwappable<T>::Value);

  template<typename T, typename U, class=void>
  struct SwappableWithHelper : FalseType {};
  template<typename T, typename U> 
  struct SwappableWithHelper<T, U, Void_t<decltype(Swap(Declval<T>(), Declval<U>()))>> : TrueType {};

  template<typename T, typename U>
  struct IsSwappableWithHelper 
    : BoolConstant<Conjunction_v<SwappableWithHelper<T, U>, SwappableWithHelper<U, T>>> {};

  template<typename T>
  struct IsSwappableHelper 
    : IsSwappableWithHelper<AddLValueReference_t<T>, AddLValueReference_t<T>>::Type {};

  template<typename T, typename U>
  struct SwapCannotThrowHelper 
    : BoolConstant<noexcept(Swap(Declval<T>(), Declval<U>())) && noexcept(Swap(Declval<U>(), Declval<T>()))> {};

  template<typename T, typename U>
  struct IsNoThrowSwappableWithHelper
    : BoolConstant<Conjunction_v<IsSwappableWithHelper<T, U>, SwapCannotThrowHelper<T, U>>> {};

  template<typename T>
  struct IsNoThrowSwappableHelper
    : IsNoThrowSwappableWithHelper<AddLValueReference_t<T>, AddLValueReference_t<T>>::Type {};
}

export namespace autl
{
  /*
  * Determine if T and U are swappable
  * Swappable if T and U satisfy an overload of Swap (standard or provided by user as extension of autl::Swap)
  * (True for lvalue with lvalue, false for basically everything else)
  */
  template<typename T, typename U>
  struct IsSwappableWith : IsSwappableWithHelper<T, U>::Type {};

  /*
  * Helper to access ::Value of IsSwappableWith
  */
  template<typename T, typename U> inline constexpr bool IsSwappableWith_v = IsSwappableWith<T, U>::Value;

  /*
  * Determine if T& is swappable with another T&
  */
  template<typename T>
  struct IsSwappable : IsSwappableHelper<T> {};

  /*
  * Helper to access ::Value of IsSwappable
  */
  template<typename T> inline constexpr bool IsSwappable_v = IsSwappable<T>::Value;

  /*
  * Determine if T and U are swappable with no chance of throwing
  * See IsSwappableWith for what satisfies swappable-with
  */
  template<typename T, typename U>
  struct IsNoThrowSwappableWith : IsNoThrowSwappableWithHelper<T, U>::Type {};

  /*
  * Helper to access ::Value of IsNoThrowSwappableWith
  */
  template<typename T, typename U> inline constexpr bool IsNoThrowSwappableWith_v = IsNoThrowSwappableWith<T, U>::Value;

  /*
  * Determine if T& is swappable with another T& with no chance of throwing
  */
  template<typename T>
  struct IsNoThrowSwappable : IsNoThrowSwappableHelper<T> {};

  /*
  * Helper to access ::Value of IsNoThrowSwappable
  */
  template<typename T> inline constexpr bool IsNoThrowSwappable_v = IsNoThrowSwappable<T>::Value;
}

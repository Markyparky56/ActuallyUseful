module;
export module autl.functional.operators;

import autl.concepts.equalitycomparable;
import autl.concepts.totallyordered;
import autl.utility.forward;

export namespace autl
{
  /*
  * Compares A and B, true if equal
  * Requires == and != operators to be valid (must pass EqualityComparableWith concept)
  */
  struct EqualTo
  {
    template<typename A, typename B>
      requires EqualityComparableWith<A, B>
    [[nodiscard]] constexpr bool operator()(A&& lhs, B&& rhs) const 
      noexcept(noexcept(static_cast<bool>(Forward<A>(lhs) == Forward<B>(rhs))))
    {
      return static_cast<bool>(Forward<A>(lhs) == Forward<B>(rhs));
    }

    using IsTransparent = void;
  };

  /*
  * Compares A and B, true is not equal
  * Requires == and != operators to be valid (must pass EqualityComparableWith concept)
  */
  struct NotEqualTo
  {
    template<typename A, typename B>
      requires EqualityComparableWith<A, B>
    [[nodiscard]] constexpr bool operator()(A&& lhs, B&& rhs) const 
      noexcept(noexcept(static_cast<bool>(!(Forward<A>(lhs) == Forward<B>(rhs)))))
    {
      return static_cast<bool>(!(Forward<A>(lhs) == Forward<B>(rhs)));
    }

    using IsTransparent = void;
  };

  /*
  * Compares A and B, true if left-hand side is less (<) than right
  * Requires all comparison operators to be valid (must pass TotallyOrderedWith concept)
  */
  struct Less
  {
    template<typename A, typename B>
      requires TotallyOrderedWith<A, B>
    [[nodiscard]] constexpr bool operator()(A&& lhs, B&& rhs) const
      noexcept(noexcept(static_cast<bool>(Forward<A>(lhs) < Forward<B>(rhs))))
    {
      return static_cast<bool>(Forward<A>(lhs) < Forward<B>(rhs));
    }

    using IsTransparent = void;
  };

  /*
  * Compares A and B, true if left-hand side is less-than or equal to right
  * Requires all comparison operators to be valid (must pass TotallyOrderedWith concept)
  */
  struct LessEqual
  {
    template<typename A, typename B>
      requires TotallyOrderedWith<A, B>
    [[nodiscard]] constexpr bool operator()(A&& lhs, B&& rhs) const
      noexcept(noexcept(static_cast<bool>(!(Forward<B>(rhs) < Forward<A>(lhs)))))
    {
      // Note: !(rhs < lhs) equivalent to lhs <= rhs
      return static_cast<bool>(!(Forward<B>(rhs) < Forward<A>(lhs)));
    }

    using IsTransparent = void;
  };

  /*
  * Compares A and B, true if left-hand side is greater than right
  * Requires all comparison operators to be valid (must pass TotallyOrderedWith concept)
  */
  struct Greater
  {
    template<typename A, typename B>
      requires TotallyOrderedWith<A, B>
    [[nodiscard]] constexpr bool operator()(A&& lhs, B&& rhs) const
      noexcept(noexcept(statc_cast<bool>(Forward<B>(rhs) < Forward<A>(lhs))))
    {
      // Note: rhs < lhs equivalent to lhs > rhs;
      return static_cast<bool>(Forward<B>(rhs) < Forward<A>(lhs));
    }

    using IsTransparent = void;
  };

  /*
  * Compares A and B, true if left-hand side is greater than or equal to right
  * Requires all comparison operators to be valid (must pass TotallyOrderedWith concept)
  */
  struct GreaterEqual
  {
    template<typename A, typename B>
      requires TotallyOrderedWith<A, B>
    [[nodiscard]] constexpr bool operator()(A&& lhs, B&& rhs) const
      noexcept(noexcept(statc_cast<bool>(!(Forward<B>(rhs) < Forward<A>(lhs)))))
    {
      // Note: rhs < lhs equivalent to lhs > rhs;
      return static_cast<bool>(!(Forward<B>(rhs) < Forward<A>(lhs)));
    }

    using IsTransparent = void;
  };

  /*
  * Returns input unmodified
  */
  struct Identity
  {
    template<typename T>
    [[nodiscard]] constexpr T&& operator()(T&& val) const
      noexcept(noexcept(Forward<T>(val)))
    {
      return Forward<T>(val);
    }

    using IsTransparent = void;
  };
}

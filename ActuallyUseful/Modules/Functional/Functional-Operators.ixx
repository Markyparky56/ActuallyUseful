module;
export module autl.functional.operators;

import autl.concepts.equalitycomparable;
import autl.concepts.totallyordered;
import autl.utility.forward;

/*
* Notes:
* IsTransparent means the operator accepts arbitrary types and uses perfect forwarding
*/

// Totally Ordered Operators in the style of std::ranges
export namespace autl::TotallyOrderedOps
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
}

// More flexible, less strict C++14 operators
export namespace autl
{
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

  /*
  * Returns the sum of the two operands
  */
  template<typename T=void>
  struct Plus
  {
    [[nodiscard]] constexpr T operator()(const T& lhs, const T& rhs) const
    {
      return lhs + rhs;
    }
  };

  /*
  * Returns the sum of the two operands
  * Specialisation of Plus with parameter and return type deduced
  */
  template<>
  struct Plus<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) + Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) + Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) + Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the difference between the two operands
  */
  template<typename T=void>
  struct Minus
  {
    [[nodiscard]] constexpr T operator()(const T& lhs, const T& rhs) const
    {
      return lhs - rhs;
    }
  };

  /*
  * Returns the difference between the two operands
  * Specialisation of Plus with parameter and return type deduced
  */
  template<>
  struct Minus<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) - Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) - Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) - Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the product of the two operands
  */
  template<typename T=void>
  struct Multiplies
  {
    [[nodiscard]] constexpr T operator()(const T& lhs, const T& rhs) const
    {
      return lhs * rhs;
    }
  };

  /*
  * Returns the product of the two operands
  * Specialisation of Multiplies with parameter and return type deduced
  */
  template<>
  struct Multiplies<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) * Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) * Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) * Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the quotient of the two operands
  */
  template<typename T=void>
  struct Divides
  {
    [[nodiscard]] constexpr T operator()(const T& lhs, const T& rhs) const
    {
      return lhs / rhs;
    }
  };

  /*
  * Returns the quotient of the two operands
  * Specialisation of Divides with parameter and return type deduced
  */
  template<>
  struct Divides<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) / Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) / Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) / Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the equality comparison of the two operands
  */
  template<typename T=void>
  struct EqualTo
  {
    [[nodiscard]] constexpr bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs == rhs;
    }
  };

  /*
  * Returns the equality comparison of the two operands
  * Specialisation of EqualTo with parameter and return type deduced
  */
  template<>
  struct EqualTo<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) == Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) == Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) == Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the inequality comparison of the two operands
  */
  template<typename T = void>
  struct NotEqualTo
  {
    [[nodiscard]] constexpr bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs != rhs;
    }
  };

  /*
  * Returns the inequality comparison of the two operands
  * Specialisation of NotEqualTo with parameter and return type deduced
  */
  template<>
  struct NotEqualTo<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) != Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) != Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) != Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the less than comparison of the two operands
  */
  template<typename T=void>
  struct Less
  {
    [[nodiscard]] constexpr bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs < rhs;
    }
  };

  /*
  * Returns the less than comparison of the two operands
  * Specialisation of Less with parameter and return type deduced
  */
  template<>
  struct Less<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) < Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) < Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) < Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the less than or equal comparison of the two operands
  */
  template<typename T = void>
  struct LessEqual
  {
    [[nodiscard]] constexpr bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs <= rhs;
    }
  };

  /*
  * Returns the less than or equal comparison of the two operands
  * Specialisation of NotEqualTo with parameter and return type deduced
  */
  template<>
  struct LessEqual<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) <= Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) <= Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) <= Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the greater than comparison of the two operands
  */
  template<typename T = void>
  struct Greater
  {
    [[nodiscard]] constexpr bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs > rhs;
    }
  };

  /*
  * Returns the greater than comparison of the two operands
  * Specialisation of NotEqualTo with parameter and return type deduced
  */
  template<>
  struct Greater<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) > Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) > Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) > Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  /*
  * Returns the greater than or equal comparison of the two operands
  */
  template<typename T = void>
  struct GreaterEqual
  {
    [[nodiscard]] constexpr bool operator()(const T& lhs, const T& rhs) const
    {
      return lhs >= rhs;
    }
  };

  /*
  * Returns the greater than comparison of the two operands
  * Specialisation of NotEqualTo with parameter and return type deduced
  */
  template<>
  struct GreaterEqual<void>
  {
    template<typename T, typename U>
    [[nodiscard]] constexpr auto operator()(T&& lhs, U&& rhs) const
      noexcept(noexcept(Forward<T&&>(lhs) >= Forward<U&&>(rhs)))
            -> decltype(Forward<T&&>(lhs) >= Forward<U&&>(rhs))
    {
      return Forward<T&&>(lhs) >= Forward<U&&>(rhs);
    }

    using IsTransparent = void;
  };

  // TODO: Bitwise ops (& | ^ ~)
  // BitAND, BitOR, BitXOR, BitNOT

  // TODO: Logical ops (AND, OR, NOT)
  // LogicalAND, LogicalOR, LogicalNOT
}

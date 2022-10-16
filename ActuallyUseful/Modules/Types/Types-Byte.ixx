module;
export module autl.types.byte;

import autl.concepts.integral;
import autl.types.arithmetic;

export namespace autl
{
  /*
  * Distinct byte type that conceptualises a byte
  * Differs from char/unsigned char in that it can be used to access raw memory but is not a character type
  * or an arithmetic type. A byte is only a collection of bits and only bitwise operators are defined for it.
  */
  enum class byte : uint8 {};

  /*
  * Equivalent to `return IntType(b)`
  */
  template<Integral IntType>
  [[nodiscard]] constexpr IntType ToInteger(byte b) noexcept
  {
    return static_cast<IntType>(b);
  }

  /*
  * Left-shift op
  */
  template<Integral IntType>
  [[nodiscard]] constexpr byte operator<<(const byte b, const IntType shift) noexcept
  {
    return byte(uint8(uint32(b) << shift));
  }

  /*
  * Right-shift op
  */
  template<Integral IntType>
  [[nodiscard]] constexpr byte operator>>(const byte b, const IntType shift) noexcept
  {
    return byte(uint8(uint32(b) >> shift));
  }

  /*
  * Left-shift assignment op
  */
  template<Integral IntType>
  constexpr byte& operator<<=(byte& b, IntType shift) noexcept
  {
    return b = b << shift;
  }

  /*
  * Right-shift assignment op
  */
  template<Integral IntType>
  constexpr byte& operator>>=(byte& b, IntType shift) noexcept
  {
    return b = b >> shift;
  }

  /*
  * Bitwise OR op
  */
  [[nodiscard]] constexpr byte operator|(const byte lhs, const byte rhs) noexcept
  {
    return byte(uint8(uint32(lhs) | uint32(rhs)));
  }

  /*
  * Bitwise AND op
  */
  [[nodiscard]] constexpr byte operator&(const byte lhs, const byte rhs) noexcept
  {
    return byte(uint8(uint32(lhs) & uint32(rhs)));
  }

  /*
  * Bitwise XOR op
  */
  [[nodiscard]] constexpr byte operator^(const byte lhs, const byte rhs) noexcept
  {
    return byte(uint8(uint32(lhs) ^ uint32(rhs)));
  }

  /*
  * Bitwise NOT op
  */
  [[nodiscard]] constexpr byte operator~(const byte b) noexcept
  {
    return byte(uint8(~uint32(b)));
  }

  /*
  * Bitwise OR assignment op
  */
  template<Integral IntType>
  constexpr byte& operator|=(byte& b, const IntType rhs) noexcept
  {
    return b = b | rhs;
  }

  /*
  * Bitwise AND assignment op
  */
  template<Integral IntType>
  constexpr byte& operator&=(byte& b, const IntType rhs) noexcept
  {
    return b = b & rhs;
  }

  /*
  * Bitwise XOR assignment op
  */
  template<Integral IntType>
  constexpr byte& operator^=(byte& b, const IntType rhs) noexcept
  {
    return b = b ^ rhs;
  }
}

export void MyFunc();
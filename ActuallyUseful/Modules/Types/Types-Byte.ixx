module;
export module autl.types.byte;

export namespace autl
{
  /*
  * Distinct byte type that conceptualises a byte
  * Differs from char/unsigned char in that it can be used to access raw memory but is not a character type
  * or an arithmetic type. A byte is only a collection of bits and only bitwise operators are defined for it.
  */
  enum class byte : unsigned char {};

  /*
  * 
  */
  template<typename IntType>
  constexpr IntType ToInteger(byte b) noexcept
  {
    return static_cast<IntType>(b);
  }

  //template<typename 

}

export void MyFunc();
module;
export module autl.type_traits.issigned;

import autl.type_traits.constvolatile;
import autl.type_traits.isintegral;
import autl.type_traits.isfloatingpoint;
import autl.type_traits.integralconstant;

namespace autl
{
  template<typename T, bool=IsIntegral_v<T>>
  struct IsSignedBase
  {
    using Type = RemoveCV_t<T>;

    // Check for underflow
    static constexpr bool Signed = static_cast<Type>(-1) < static_cast<T>(0);
    static constexpr bool Unsigned = !Signed;
  };

  template<typename T>
  struct IsSignedBase<T, false>
  {
    // floating-point is signed
    // non-integral, non-floating point is neither signed nor unsigned
    static constexpr bool Signed = IsFloatingPoint_v<T>;
    static constexpr bool Unsigned = false;
  };
}

export namespace autl
{
  /*
  * Determines if given type is signed
  * floating-point types are always signed
  * non-arithemtic types are neither signed nor unsigned
  */
  template<typename T> struct IsSigned : BoolConstant<IsSignedBase<T>::Signed> {};

  /*
  * Helper to access ::Value of IsSigned
  */
  template<typename T> inline constexpr bool IsSigned_v = IsSigned<T>::Value;

  /*
  * Determines if given type is unsigned
  * float-point types are always signed
  * non-arithemtic types are neither signed nor unsigned
  */
  template<typename T> struct IsUnsigned : BoolConstant<IsSignedBase<T>::Unsigned> {};

  /*
  * Helper to access ::Value of IsUnsigned
  */
  template<typename T> inline constexpr bool IsUnsigned_v = IsUnsigned<T>::Value;
}

module;
export module autl.type_traits.isintegral;

import autl.type_traits.logical;
import autl.type_traits.integralconstant;
import autl.type_traits.constvolatile;

export namespace autl
{
  /*
  * Is given type T any of the integral (int) types
  */
  export template<typename T> struct IsIntegral
    : BoolConstant<IsAnyOf_v<RemoveCV_t<T>
    , bool
    , char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t
    , short, unsigned short
    , int, unsigned int
    , long, unsigned long
    , long long, unsigned long long>> {};

  /*
  * Helper to access ::Value of IsIntegral
  */
  export template<typename T> inline constexpr bool IsIntegral_v = IsIntegral<T>::Value;
}

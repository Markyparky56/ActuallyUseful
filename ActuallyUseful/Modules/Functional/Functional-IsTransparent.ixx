module;
export module autl.functional.istransparent;

import autl.type_traits.integralconstant;
import autl.type_traits.isvoid;

export namespace autl
{
  /*
  * TrueType if T defines IsTransparent
  */
  template<typename T, typename = void> struct IsTransparent : FalseType {};
  template<typename T> 
  struct IsTransparent<T, Void_t<typename T::IsTransparent>> : TrueType{};

  /*
  * Helper to access ::Value of IsTransparent
  */
  template<typename T> inline constexpr bool IsTransparent_v = IsTransparent<T>::Value;
}

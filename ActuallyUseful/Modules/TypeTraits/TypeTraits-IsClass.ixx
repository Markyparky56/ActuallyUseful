module;
export module autl.type_traits.isclass;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determines if given type is a class
  */
  template<typename T> struct IsClass : BoolConstant<__is_class(T)> {};

  /*
  * Helper to access ::Value of IsClass
  */
  template<typename T> inline constexpr bool IsClass_v = IsClass<T>::Value;
}

module;
export module autl.type_traits.ispolymorphic;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determine is T is a polymorphic class
  * A polymorphic class is a non-union class that declare or inherits at least one virtual function
  */
  template<typename T> struct IsPolymorphic : BoolConstant<__is_polymorphic(T)> {};

  /*
  * Helper to access ::Value of IsPolymorphic
  */
  template<typename T> inline constexpr bool IsPolymorphic_v = IsPolymorphic<T>::Value;
}

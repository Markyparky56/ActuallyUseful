module;
export module autl.type_traits.hasvirtualdestructor;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determine if T has a virtual destructor
  * If true, T can be derived from and the derived object can be safely deleted from a pointer to the base
  */
  template<typename T> struct HasVirtualDestructor : BoolConstant<__has_virtual_destructor(T)> {};

  /*
  * Helper to access ::Value of HasVirtualDestructor
  */
  template<typename T> inline constexpr bool HasVirtualDestructor_v = HasVirtualDestructor<T>::Value;
}

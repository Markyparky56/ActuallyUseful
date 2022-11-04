module;
export module autl.type_traits.isabstract;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determine is T is an abstract class
  * An abstract class is a non-union class that declare or inherits at least one pure virtual function
  */
  template<typename T> struct IsAbstract : BoolConstant<__is_abstract(T)> {};

  /*
  * Helper to access ::Value of IsAbstract
  */
  template<typename T> inline constexpr bool IsAbstract_v = IsAbstract<T>::Value;
}

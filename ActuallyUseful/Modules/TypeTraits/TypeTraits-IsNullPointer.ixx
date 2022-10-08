module;
export module autl.type_traits.isnullptr;

import autl.types.std;
import autl.type_traits.constvolatile;
import autl.type_traits.logical;

export namespace autl
{
  /*
  * Determine if given type is of type nullptr_t
  */
  template<typename T> struct IsNullPointer : IsSame<nullptr_t, RemoveCV_t<T>> {};

  /*
  * Helper to access ::Value of IsNullPointer
  */
  template<typename T> inline constexpr bool IsNullPointer_v = IsNullPointer<T>::Value;
}

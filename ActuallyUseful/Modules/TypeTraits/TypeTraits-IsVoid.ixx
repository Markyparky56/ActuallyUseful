module;
export module autl.type_traits.isvoid;

import autl.type_traits.logical;
import autl.type_traits.constvolatile;

export namespace autl
{
  /*
  * void utility metafunction
  */
  template<typename...> using Void_t = void;

  /*
  * Checks whether T is a void type
  */
  template<typename T> struct IsVoid : IsSame<void, typename RemoveCV_t<T>> {};

  /*
  * Helper to access ::Value of IsVoid
  * Constant value corresponding to if T is a void type
  */
  template<typename T> inline constexpr bool IsVoid_v = IsVoid<T>::Value;
}

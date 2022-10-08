module;
export module autl.type_traits.removecvref;

import autl.type_traits.constvolatile;
import autl.type_traits.reference;

export namespace autl
{
  /*
  * Combined RemoveCV and RemoveReference functionality
  */
  template<typename T> struct RemoveCVRef { using Type = RemoveCV_t<RemoveReference_t<T>>; };

  /*
  * Helper to access ::Type of RemoveCVRef
  */
  template<typename T> using RemoveCVRef_t = typename RemoveCVRef<T>::Type;
}

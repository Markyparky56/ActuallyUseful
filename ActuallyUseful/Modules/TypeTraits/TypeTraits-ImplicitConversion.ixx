module;
export module autl.type_traits.implicitconversion;

import autl.type_traits.core;
import autl.type_traits.enableif;
import autl.type_traits.logical;
import autl.type_traits.pointer;
import autl.type_traits.reference;

export namespace autl
{
  /*
  * Implicit conversion to create an instance of a specific type
  * Safer than a C-style cast or static_cast as it does not allow down-casting
  * Useful to circumvent unintended type deduction in templates
  * Restricted to pointer/reference types to avoid egregious copying
  */
  template<typename T, EnableIf_t<IsPointer_v<T>||IsReference_v<T>,bool> = true>
  T ImplicitConversion(typename TypeIdentity<T>::Type arg)
  {
    return arg;
  }
}
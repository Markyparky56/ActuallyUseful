module;
export module autl.type_traits.isobject;

import autl.type_traits.integralconstant;
import autl.type_traits.isscalar;
import autl.type_traits.isarray;
import autl.type_traits.isunion;
import autl.type_traits.isclass;

export namespace autl
{
  /*
  * Determines if type is an object type
  * An object is any type other than function, reference, or void
  */
  template<typename T> struct IsObject
    : BoolConstant<IsScalar_v<T> || IsArray_v<T> || IsUnion_v<T> || IsClass_v<T>>
  {};

  /*
  * Helper to access ::Value of IsObject
  */
  template<typename T> inline constexpr bool IsObject_v = IsObject<T>::Value;
}

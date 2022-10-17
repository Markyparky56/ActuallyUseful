module;
export module autl.type_traits.isstandardlayout;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * True if T is a standard-layout type
  * Standard-layout types are:
  * - scalar types (arithmetic, enum, pointer, pointer-to-member)
  * - standard-layout class types, which are defined as:
  *   - have no non-static data members which are themselves non-standard classes/arrays/references
  *   - have no virtual functions and no virtual base classes
  *   - have the same access control (public/protected/private) for all non-static data members
  *   - have no non-standard-layout base classes
  *   - only one class in the hierarchy has non-static data members
  *   - None of the base classes has the same type as the first non-static data member
  * Standard-layout types can be cast to a pointer to their first-member and back safely
  */
  template<typename T>
  struct IsStandardLayout : BoolConstant<__is_standard_layout(T)> {};

  /*
  * Helper to access ::Value of IsStandardLayout
  */
  template<typename T> inline constexpr bool IsStandardLayout_v = IsStandardLayout<T>::Value;
}

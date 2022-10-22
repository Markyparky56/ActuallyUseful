module;
export module autl.type_traits.hasuniqueobjectrepresentations;

import autl.type_traits.integralconstant;
import autl.type_traits.constvolatile;
import autl.type_traits.removeextent;

export namespace autl
{
  /*
  * True if T has a unique object representation
  * Meaning:
  * Is trivially copyable
  * Two objects of type T will have the same value representation (each member is equal)
  * and the same object repsentation (comparing each byte for equality)
  * This is generally true for packed structs of ints, but structs with types which cause padding to be inserted
  * can cause this to be false. 
  * Float types (or types containing floats) may not necessarily be true since binary equality and floating-point equality are not the same thing
  */
  template<typename T>
  struct HasUniqueObjectRepresentations 
    : public BoolConstant<__has_unique_object_representations(RemoveCV_t<RemoveAllExtents_t<T>>)> {};

  /*
  * Helper to access ::Value of HasUniqueObjectRepresentations
  */
  template<typename T> 
  inline constexpr bool HasUniqueObjectRepresentations_v = HasUniqueObjectRepresentations<T>::Value;
}
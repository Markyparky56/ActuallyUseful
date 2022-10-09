module;
export module autl.type_traits.reference;

import autl.type_traits.core;
import autl.type_traits.integralconstant;
import autl.type_traits.isvoid;

// Unexported internals
namespace autl
{
  // non-referenceable type
  template<typename T, typename=void>
  struct AddReference
  {
    using LValue = T;
    using RValue = T;
  };

  // referencable type
  template<typename T>
  struct AddReference<T, Void_t<T&>>
  {
    using LValue = T&;
    using RValue = T&&;
  };
}

/*
* ActuallyUseful Type Traits
* 
* AddLValueReference
* AddLValueReference_t
* 
* AddRValueReference
* AddRValueReference_t
* 
* RemoveReference
* RemoveReference_t
*/
export namespace autl
{
  /*
  * Determines if given type is a reference, accessible via ::Value
  */
  template<typename T> struct IsReference : FalseType {};
  template<typename T> struct IsReference<T&> : TrueType {};
  template<typename T> struct IsReference<T&&> : TrueType {};

  /*
  * Helper to access ::Value of IsReference
  */
  template<typename T> inline constexpr bool IsReference_v = IsReference<T>::Value;

  /*
  * Determines if given type is an lvalue reference (T&)
  */
  template<typename T> struct IsLValueReference : FalseType {};
  template<typename T> struct IsLValueReference<T&> : TrueType {};

  /*
  * Helper to access ::Value of IsLValueReference
  */
  template<typename T> inline constexpr bool IsLValueReference_v = IsLValueReference<T>::Value;

  /*
  * Determines if given type is an rvalue reference (T&&)
  */
  template<typename T> struct IsRValueReference : FalseType {};
  template<typename T> struct IsRValueReference<T&&> : TrueType {};

  /*
  * Helper to access ::Value of IsRValueReference
  */
  template<typename T> inline constexpr bool IsRValueReference_v = IsRValueReference<T>::Value;

  /*
  * Add lvalue reference to given type
  */
  template<typename T> struct AddLValueReference { using Type = typename AddReference<T>::LValue; };
  /*
  * Helper to access ::Type of AddLValueReference  
  */
  template<typename T> using AddLValueReference_t = typename AddLValueReference<T>::Type;

  /*
  * Add rvalue reference to given type
  */
  template<typename T> struct AddRValueReference { using Type = typename AddReference<T>::RValue; };
  /*
  * Helper to access ::Type of AddRValueReference
  */
  template<typename T> using AddRValueReference_t = typename AddRValueReference<T>::Type;

  /*
  * Remove any references from a type
  */
  template<typename T> struct RemoveReference       { using Type = T; };
  template<typename T> struct RemoveReference<T&>   { using Type = T; };
  template<typename T> struct RemoveReference<T&&>  { using Type = T; };

  /*
  * Helper to access ::Type of RemoveReference
  */
  template<typename T> using RemoveReference_t = typename RemoveReference<T>::Type;
}

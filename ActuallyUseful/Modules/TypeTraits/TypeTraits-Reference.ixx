module;
export module autl.type_traits.reference;

import autl.type_traits.types;

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

  template<typename T> AddRValueReference_t<T> declval() noexcept
  {
    static_assert(AlwaysFalse<T>, "Calling declval is ill-formed as per N4892 specifications");
  }

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

module;
export module autl.type_traits.pointer;

import autl.type_traits.types;
import autl.type_traits.reference;

namespace autl::impl
{
  // pointer type cannot be formed
  template<typename T, typename=void>
  struct AddPointer
  {
    using Type = T;
  };

  // pointer type can be formed
  template<typename T>
  struct AddPointer<T, Void_t<RemoveReference_t<T>*>>
  {
    using Type = RemoveReference_t<T>*;
  };
}

export namespace autl
{
  /*
  * If given type is a reference type, provide Type as a pointer to the referred type
  * If given type is an object type, a function type that is not cv- or ref-qualified, or a void type, provides T*
  * If unable to perform above, Type will be T
  */
  template<typename T> struct AddPointer { using Type = impl::AddPointer<T>::Type; };

  /*
  * Helper to access ::Type of AddPointer  
  */
  template<typename T> using AddPointer_t = typename AddPointer<T>::Type;

  /*
  * Remove one level of pointer from a type
  */
  template<typename T> struct RemovePointer { using Type = T; };
  template<typename T> struct RemovePointer<T*> { using Type = T; };
  template<typename T> struct RemovePointer<T* const> { using Type = T; };
  template<typename T> struct RemovePointer<T* volatile> { using Type = T; };
  template<typename T> struct RemovePointer<T* const volatile> { using Type = T; };

  /*
  * Helper to access ::Type of RemovePointer
  */
  template<typename T> using RemovePointer_t = typename RemovePointer<T>::Type;
}
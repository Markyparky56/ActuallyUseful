module;
export module autl.type_traits.decay;

import autl.type_traits.logical;
import autl.type_traits.pointer;
import autl.type_traits.isfunction;
import autl.type_traits.removeextent;
import autl.type_traits.reference;
import autl.type_traits.constvolatile;
import autl.type_traits.isarray;

export namespace autl
{
  /*
  * Applies lvalue-to-rvalue, array-to-pointer, and funtion-to-pointer implicit conversions
  * Removes CV-qualifiers
  */
  template<typename T> struct Decay
  {
  private:
    // For internal-use only
    using U = RemoveReference_t<T>;
  public:
    using Type = typename Conditional_t<
      IsArray_v<U>,
      /*true*/  RemoveExtent_t<U>*,
      /*false*/ Conditional_t<
        IsFunction_v<U>,
        /*true*/  AddPointer_t<U>,
        /*false*/ RemoveCV_t<U>
      >
    >;
  };

  /*
  * Helper to access ::Type of Decay
  */
  template<typename T> using Decay_t = typename Decay<T>::Type;
}

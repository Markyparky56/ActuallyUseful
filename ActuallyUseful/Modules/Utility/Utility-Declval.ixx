module;
export module autl.utility.declval;

import autl.type_traits.core;
import autl.type_traits.reference;

export namespace autl
{
  /*
  * Convert any type T to a reference type, making it possible to use member functions in the operand of decltype
  * This eliminates the need to construct the object
  * Commonly used by templates where inputs may not share a common constructor but have a common member function
  * Cannot be used in evaluated contexts
  */
  template<typename T> AddRValueReference_t<T> Declval() noexcept
  {
    // Cannot call declval in an evaluated context
    static_assert(AlwaysFalse<T>, "Calling declval is ill-formed as per N4892 specifications");
  }
}

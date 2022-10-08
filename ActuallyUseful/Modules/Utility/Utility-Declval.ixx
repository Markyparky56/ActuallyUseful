module;
export module autl.utility.declval;

import autl.type_traits.reference;

export namespace autl
{
  template<typename T> AddRValueReference_t<T> Declval() noexcept
  {
    // Cannot call declval in an evaluated context
    static_assert(AlwaysFalse<T>, "Calling declval is ill-formed as per N4892 specifications");
  }
}

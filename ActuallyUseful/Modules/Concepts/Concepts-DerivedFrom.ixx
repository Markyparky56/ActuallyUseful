module;
export module autl.concepts.derivedfrom;

import autl.type_traits.logical;
import autl.type_traits.convertible;

export namespace autl
{
  /*
  * Satisified if and only if Base is the same type as Derived or if Base is an unambiguous public base of Derived
  * Ignores cv-qualifiers
  * Note: behaviour differs from IsBaseOf when Base is a private or protected base of Derived
  */
  template<typename Derived, typename Base>
  concept DerivedFrom = IsBaseOf_v<Base, Derived> && IsConvertible_v<const volatile Derived*, const volatile Base*>;
}

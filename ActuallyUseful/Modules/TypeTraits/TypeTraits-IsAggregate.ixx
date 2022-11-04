module;
export module autl.type_traits.isaggregate;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * Determine is T is an aggregate type
  * An aggregate type is either:
  * - an array type
  * - a class type (typically a struct or union) where
  *   - It has no private or protected non-static members
  *   - No user-provided, inherited, or explicit constructors
  *   - No user-declared or inherited constructors
  *   - No virtual, private, or protected base classes
  *   - No virtual member functions
  */
  template<typename T> struct IsAggregate : BoolConstant<__is_aggregate(T)> {};

  /*
  * Helper to access ::Value of IsAggregate
  */
  template<typename T> inline constexpr bool IsAggregate_v = IsAggregate<T>::Value;
}

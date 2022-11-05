module;
export module autl.type_traits.integralconstant;

/*
* ActuallyUseful Type Traits
* 
* Integral Constant + BoolConstant
* TrueType and FalseType aliases
*/
export namespace autl
{
  /*
  * Wrapper for compile-time constant of specified value
  */
  template<typename T, T value>
  struct IntegralConstant
  {
    using ValueType = T;
    using Type = IntegralConstant;
    static constexpr ValueType Value = value;
    constexpr operator ValueType() const noexcept { return Value; }
    constexpr ValueType operator()() const noexcept { return Value; }
  };

  /*
  * Helper alias of IntegralConstant where T is bool
  */
  template<bool B> using BoolConstant = IntegralConstant<bool, B>;
  /*
  * Helper alias for BoolConstant<true>
  */
  using TrueType = BoolConstant<true>;
  /*
  * Helper alias for BoolConstant<false>
  */
  using FalseType = BoolConstant<false>;
}
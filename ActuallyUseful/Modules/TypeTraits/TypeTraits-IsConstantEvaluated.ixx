module;
export module autl.type_traits.isconstantevaluated;

export namespace autl
{
  /*
  * Detect whether the function call occurs within a constant-evaluated context
  */
  [[nodiscard]] inline constexpr bool IsConstantEvaluated() noexcept
  {
    return __builtin_is_constant_evaluated();
  }

  // Possible in C++23, requires `if consteval`
  //[[nodiscard]] inline constexpr bool IsConstantEvaluated() noexcept
  //{
  //  if consteval
  //  {
  //    return true;
  //  }
  //  else
  //  {
  //    return false;
  //  }
  //}
}
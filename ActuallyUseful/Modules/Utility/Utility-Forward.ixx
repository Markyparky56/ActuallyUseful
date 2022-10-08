module;
export module autl.utility.forward;

import autl.type_traits.reference;

export namespace autl
{
  /*
  * Forward an lvalue as either an lvalue or an rvalue
  */
  template<typename T>
  [[nodiscard]] constexpr T&& Forward(RemoveReference_t<T>& arg) noexcept
  {
    return static_cast<T&&>(arg);
  }

  /*
  * Forward an rvalue as an rvalue
  */
  template<typename T>
  [[nodiscard]] constexpr T&& Forward(RemoveReference_t<T>&& arg) noexcept
  {
    static_assert(!IsLValueReference_v<T>, "Bad Forward Call");
    return static_cast<T&&>(arg);
  }
}

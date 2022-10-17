module;
export module autl.utility.forward;

import autl.type_traits.reference;
import autl.type_traits.implicitconversion;
import autl.type_traits.constvolatile;

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
    static_assert(!IsLValueReference_v<T>, "Cannot forward an rvalue as an lvalue");
    return static_cast<T&&>(arg);
  }

  /*
  * Cast an lvalue to an rvalue of a base class
  * NOTE: Not entirely clear on the decltype = nullptr used here, needs further research
  * NOTE: How similar is this to std::forward_like?
  */
  template<typename T, typename Base,
    decltype(ImplicitConversion<const volatile Base*>(static_cast<RemoveReference_t<T>*>(nullptr)))* = nullptr>
  [[nodiscard]] constexpr auto ForwardAsBase(RemoveReference_t<T>& arg) noexcept
    -> decltype(static_cast<TransferCVRef_t<T&&, Base>>(arg))
  {
    return static_cast<TransferCVRef_t<T&&, Base>>(arg);
  }
  template<typename T, typename Base,
    decltype(ImplicitConversion<const volatile Base*>(static_cast<RemoveReference_t<T>*>(nullptr)))* = nullptr>
  [[nodiscard]] constexpr auto ForwardAsBase(RemoveReference_t<T>&& arg) noexcept
    -> decltype(static_cast<TransferCVRef_t<T&&, Base>>(arg))
  {
    return static_cast<TransferCVRef_t<T&&, Base>>(arg);
  }
}

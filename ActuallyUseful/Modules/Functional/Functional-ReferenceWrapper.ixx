module;
export module autl.functional.referencewrapper;

import autl.type_traits.enableif;
import autl.type_traits.logical;
import autl.type_traits.removecvref;
import autl.type_traits.core;
import autl.type_traits.integralconstant;
import autl.utility.declval;
import autl.memory.addressof;

namespace autl
{
  template<typename T> void RefwrapCtorFunc(TypeIdentity_t<T&>) noexcept; // undefined dummy func
  template<typename T> void RefwrapCtorFunc(TypeIdentity_t<T&&>) = delete;

  template<typename T, typename U, typename=void>
  struct RefwrapHasCtorFrom : FalseType {};

  template<typename T, typename U>
  struct RefwrapHasCtorFrom<T, U, Void_t<decltype(RefwrapCtorFunc<T>(Declval<U>()))>> : TrueType {};
}

export namespace autl
{
  template<typename T>
  class ReferenceWrapper
  {
  public:
    // TODO: static assert IsObject_v || IsFunction_v

    using Type = T;

    template<typename U, EnableIf<Conjunction_v<Negation<IsSame<RemoveCVRef_t<U>, ReferenceWrapper>>, RefwrapHasCtorFrom<T, U>>, int> = 0>
    constexpr ReferenceWrapper(U&& val) noexcept(noexcept(RefwrapCtorFunc<T>(Declval<U>())))
    {
      T& ref = static_cast<U&&>(val);
      Ptr = AddressOf(ref);
    }

    constexpr operator T& () const noexcept
    {
      return *Ptr;
    }

    [[nodiscard]] constexpr T& Get() const noexcept
    {
      return *Ptr;
    }

    template<typename... Ts>
    constexpr auto operator()(Ts&&... args) const noexcept(noexcept)

  private:
    T* Ptr{};
  };
}

module;
export module autl.functional.referencewrapper;

import autl.type_traits.enableif;
import autl.type_traits.logical;
import autl.type_traits.removecvref;
import autl.type_traits.core;
import autl.type_traits.integralconstant;
import autl.type_traits.isvoid;
import autl.type_traits.decay;
import autl.type_traits.isfunction;
import autl.utility.declval;
import autl.memory.addressof;
import autl.functional.invoke;

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
  /*
  * Class template wrapping a reference in a copyable, assignable object
  * Can be used as a mechanism to store references inside containers which cannot normally hold references
  * CopyConstructable & CopyAssignable wrapper around a reference to an object or function of type T
  * Implicitly convertible to T&
  * If the stored reference is Callable, ReferenceWrapper is callable with the same arguments
  */
  template<typename T>
  class ReferenceWrapper
  {
  private:
    T* Ptr{};

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
    constexpr auto operator()(Ts&&... args) const noexcept(noexcept(Invoke(*Ptr, static_cast<Ts&&>(args)...)))
      -> decltype(Invoke(*Ptr, static_cast<Ts&&>(args)...))
    {
      return Invoke(*Ptr, static_cast<Ts&&>(args)...);
    }


  };

  /*
  * Deduction guide
  */
  template<typename T>
  ReferenceWrapper(T&) -> ReferenceWrapper<T>;

  /*
  * Helper to construct ReferenceWrapper from reference
  */
  template<typename T>
  [[nodiscard]] constexpr ReferenceWrapper<T> Ref(T& val) noexcept
  {
    return ReferenceWrapper<T>(val);
  }

  // Delete const rvalue Ref
  template<typename T> void Ref(const T&&) = delete;

  /*
  * Ref called with ReferenceWrapper returns new ReferenceWrapper
  */
  template<typename T>
  [[nodiscard]] constexpr ReferenceWrapper<T> Ref(ReferenceWrapper<T> val) noexcept
  {
    return val;
  }

  /*
* Helper to construct ReferenceWrapper from const reference
*/
  template<typename T>
  [[nodiscard]] constexpr ReferenceWrapper<const T> CRef(const T& val) noexcept
  {
    return ReferenceWrapper<const T>(val);
  }

  // Delete const rvalue CRef
  template<typename T> void CRef(const T&&) = delete;

  /*
  * CRef called with ReferenceWrapper returns new ReferenceWrapper but with const T
  */
  template<typename T>
  [[nodiscard]] constexpr ReferenceWrapper<const T> Ref(ReferenceWrapper<T> val) noexcept
  {
    return val;
  }

  /*
  * Retrieve Type of ReferenceWrapper (returns given T otherwise)
  */
  template<typename T> struct UnwrapReference { using Type = T; };
  template<typename T> struct UnwrapReference<ReferenceWrapper<T>> { using Type = T&; };

  /*
  * Helper to access ::Type of UnwrapReference
  */
  template<typename T> using UnwrapReference_t = typename UnwrapReference<T>::Type;

  /*
  * Decay type, or if it's a ReferenceWrapper, decay the wrapped type
  */
  template<typename T> struct UnwrapRefDecay { using Type = UnwrapReference_t<Decay_t<T>>; };
 
  /*
  * Helper to access ::Type of UnwrapRefDecay
  */
  template<typename T> using UnwrapRefDecay_t = typename UnwrapRefDecay<T>::Type;
}

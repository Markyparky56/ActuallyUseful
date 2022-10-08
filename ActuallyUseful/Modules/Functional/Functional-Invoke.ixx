module;
export module autl.functional.invoke;

namespace autl
{
  // Forward declare ReferenceWrapper and cross our fingers it works (templates do be magic)
  template<typename T> class ReferenceWrapper;

  // Assuming pmf is pointer-to-member-function
  // and pmd is pointer-to-member-data?
  enum class InvokerStrategy
  {
    Functor,
    PMF_Object,
    PMF_Refwrap,
    PMF_Pointer,
    PMD_Object,
    PMD_Refwrap,
    PMD_Pointer
  };

  struct InvokerFunctor
  {
    static constexpr InvokerStrategy Strategy = InvokerStrategy::Functor;

    template<typename Callable, typename... Ts>
    static constexpr auto Call(Callable&& obj, Ts&&... args) noexcept(noexcept(static_cast<Callable&&>(obj)(static_cast<Ts&&>(args)...)))
      -> decltype(static_cast<Callable&&>(obj)(static_cast<Ts&&>(args)...))
    {
      return static_cast<Callable&&>(obj)(static_cast<Ts&&>(args)...);
    }
  };

  struct InvokerPMFObject
  {
    static constexpr InvokerStrategy Strategy = InvokerStrategy::PMF_Object;

    template<typename Decayed, typename T, typename... Ts>
    static constexpr auto Call(Decayed pmf, T&& arg1, Ts&&... args) noexcept(noexcept((static_cast<T&&>(arg1).*pmf)(static_cast<Ts&&>(args)...)))
      -> decltype((static_cast<T&&>(arg1).*pmf)(static_cast<Ts&&>(args)...))
    {
      return (static_cast<T&&>(arg1).*pmf)(static_cast<Ts&&>(args)...);
    }
  };

  struct InvokerPMFRefwrap
  {
    static constexpr InvokerStrategy Strategy = InvokerStrategy::PMD_Refwrap;

    template<typename Decayed, typename Refwrap, typename... Ts>
    static constexpr auto Call(Decayed pmf, Refwrap rw, Ts&&... args) noexcept(noexcept((rw.Get().*pmf)(static_cast<Ts&&>(args)...)))
      -> decltype((rw.Get().*pmf)(static_cast<Ts&&>(args)...))
    {
      return (rw.Get().*pmf)(static_cast<Ts&&>(args)...);
    }
  };

  struct InvokerPMFPointer
  {
    static constexpr InvokerStrategy Strategy = InvokerStrategy::PMF_Pointer;

    template<typename Decayed, typename T, typename... Ts>
    static constexpr auto Call(Decayed pmf, T&& arg1, Ts&&... args) noexcept(noexcept(((*static_cast<T&&>(arg1)).*pmf)(static_cast<Ts&&>(args)...)))
      -> decltype(((*static_cast<T&&>(arg1)).*pmf)(static_cast<Ts&&>(args)...))
    {
      return ((*static_cast<T&&>(arg1)).*pmf)(static_cast<Ts&&>(args)...);
    }
  };

  struct InvokerPMDObject
  {
    static constexpr InvokerStrategy Strategy = InvokerStrategy::PMD_Object;

    template<typename Decayed, typename T>
    static constexpr auto Call(Decayed pmd, T&& arg) noexcept -> decltype(static_cast<T&&>(arg).*pmd)
    {
      return static_cast<T&&>(arg).*pmd;
    }
  };

  struct InvokerPMDRefwrap
  {
    static constexpr InvokerStrategy Strategy = InvokerStrategy::PMD_Refwrap;

    template<typename Decayed, typename Refwrap>
    static constexpr auto Call(Decayed pmd, Refwrap rw) noexcept -> decltype(rw.Get().*pmd)
    {
      return rw.Get().*pmd;
    }
  };

  struct InvokerPMDPointer
  {
    static constexpr InvokerStrategy Strategy = InvokerStrategy::PMD_Pointer;

    template<typename Decayed, typename T>
    static constexpr auto Call(Decayed pmd, T&& arg) noexcept(noexcept((*static_cast<T&&>(arg)).*pmd))
      -> decltype((*static_cast<T&&>(arg)).*pmd)
    {
      return (*static_cast<T&&>(arg)).*pmd;
    }
  };

  // TODO: Invoker1 onwards
}

export namespace autl
{

}

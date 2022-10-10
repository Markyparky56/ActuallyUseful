// The contents of this file are shared between Function-Invoke and TypeTraits-Invocable
// I couldn't find a way to cleanly share these purely internal structures without leaking them as exports
// Perhaps there's something that can be done with internal module partitions but those might interfere with 
// the templates, and seem limited to a single module rather than sharing between two interfaces

import autl.type_traits.integralconstant;
import autl.type_traits.pointer;
import autl.type_traits.removecvref;
import autl.type_traits.logical;
import autl.type_traits.enableif;
import autl.type_traits.isfunction;
import autl.type_traits.reference;
import autl.type_traits.isspecialisation;

namespace autl
{
  template<typename T>
  struct IsMemberFunctionPointerHelper
  {
    using BoolType = FalseType;
  };
  template<typename Ret, typename CType>
  struct IsMemberFunctionPointerHelper<Ret CType::*>
  {
    using BoolType = TrueType; // Infer
    using ClassType = CType;
  };

  template<typename T>
  struct IsMemberObjectPointerHelper
  {
    using BoolType = FalseType;
  };
  template<typename Ret, typename CType>
  struct IsMemberObjectPointerHelper<Ret CType::*>
  {
    using BoolType = BoolConstant<!IsFunction_v<Ret>>;
    using ClassType = CType;
  };
}

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

  template<typename Callable, typename T, typename RemovedCVRef = RemoveCVRef_t<Callable>,
    bool bIsPMF = IsMemberFunctionPointer_v<RemovedCVRef>,
    bool bIsPMD = IsMemberObjectPointer_v<RemovedCVRef>>
    struct Invoker;

  template<typename Callable, typename T, typename RemovedCVRef>
  struct Invoker<Callable, T, RemovedCVRef, true, false>
    : Conditional_t<IsBaseOf_v<typename IsMemberFunctionPointerHelper<RemovedCVRef>::ClassType, RemoveReference_t<T>>,
    /*true*/  InvokerPMFObject,
    /*false*/ Conditional_t<IsSpecialisation_v<RemoveCVRef_t<T>, ReferenceWrapper>,
    /*true*/  InvokerPMFRefwrap,
    /*false*/ InvokerPMFPointer>> {};

  template<typename Callable, typename T, typename RemovedCVRef>
  struct Invoker<Callable, T, RemovedCVRef, false, true>
    : Conditional_t<IsBaseOf_v<typename IsMemberObjectPointerHelper<RemovedCVRef>::ClassType, RemoveReference_t<T>>,
    /*true*/  InvokerPMDObject,
    /*false*/ Conditional_t<IsSpecialisation_v<RemoveCVRef_t<T>, ReferenceWrapper>,
    /*true*/  InvokerPMDRefwrap,
    /*false*/ InvokerPMDPointer>> {};

  template<typename Callable, typename T, typename RemoveCVRef>
  struct Invoker<Callable, T, RemoveCVRef, false, false>
    : InvokerFunctor {};
}

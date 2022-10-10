module;
export module autl.functional.invoke;

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

export namespace autl
{
  /*
  * Invoke callable object, parameterless variant
  */
  template<typename Callable>
  constexpr auto Invoke(Callable&& obj) noexcept(noexcept(static_cast<Callable&&>(obj)()))
    -> decltype(static_cast<Callable&&>(obj)())
  {
    return static_cast<Callable&&>(obj)();
  }

  /*
  * Invoke callable object with parameters
  */
  template<typename Callable, typename T, typename... Ts>
  constexpr auto Invoke(Callable&& obj, T&& arg1, Ts&&... args) noexcept(noexcept(Invoker<Callable, T>::Call(static_cast<Callable&&>(obj), static_cast<T&&>(arg1), static_cast<Ts&&>(args)...)))
    -> decltype(Invoker<Callable, T>::Call(static_cast<Callable&&>(obj), static_cast<T&&>(arg1), static_cast<Ts&&>(args)...))
  {
    if constexpr (Invoker<Callable, T>::Strategy == InvokerStrategy::Functor)
    {
      return static_cast<Callable&&>(obj)(static_cast<T&&>(arg1), static_cast<Ts&&>(args)...);
    }
    else if constexpr (Invoker<Callable, T>::Strategy == InvokerStrategy::PMF_Object)
    {
      return (static_cast<T&&>(arg1).*obj)(static_cast<Ts&&>(args)...);
    }
    else if constexpr (Invoker<Callable, T>::Strategy == InvokerStrategy::PMF_Refwrap)
    {
      return (arg1.Get().*obj)(static_cast<Ts&&>(args)...);
    }
    else if constexpr (Invoker<Callable, T>::Strategy == InvokerStrategy::PMF_Pointer)
    {
      return ((*static_cast<T&&>(arg1)).*obj)(static_cast<Ts&&>(args)...);
    }
    else if constexpr (Invoker<Callable, T>::Strategy == InvokerStrategy::PMD_Object)
    {
      return static_cast<T&&>(arg1).*obj;
    }
    else if constexpr (Invoker<Callable, T>::Strategy == InvokerStrategy::PMD_Refwrap)
    {
      return arg1.Get().*obj;
    }
    else
    {
      static_assert(Invoker<Callable, T>::Strategy == InvokerStrategy::PMD_Pointer, "Unhandled InvokerStrategy");
      return (*static_cast<T&&>(arg1)).*obj;
    }
  }
}

/*
From a previous iteration of this file where I almost reimplemented IsMemberFunctionPointer by accident, can't bring
myself to delete it yet

//  // Base class for member function pointer predicates
//  // This is used over the existing IsMemberFunctionPointer as we add a ClassType used in Invoker
//  template<typename T>
//  struct IsMemFunPtr
//  {
//    using BoolType = FalseType;
//  };
//
//  // MSVC gets a little crazy with macros here, but it's still easier to follow than whatever GCC or Clang do
//  // A bit disgusting to mix templates and macros, but I don't blame them for not wanting to write this by hand
//#include "Invoke-DefMemberCallMacros.h"
//#define ISMEMFUNPTR(CallOpt, CVOpt, RefOpt, NoExceptOpt)                        \
//  template<typename Ret, typename Arg0, typename... Types>                      \
//  struct IsMemFunPtr<Ret (CallOpt Arg0::*)(Types...) CVOpt RefOpt NoExceptOpt>  \
//  {                                                                             \
//    using BoolType = TrueType;                                                  \
//    using ClassType = Arg0;                                                     \
//    using GuideType = EnableIf<!IsSame<int RefOpt, int&&>, Ret(Types...)>;      \
//  };
//
//  // Specialise IsMemFunPtr with every possible combination of const, volatile, &, && and noexcept
//  MEMBER_CALL_CV_REF_NOEXCEPT(ISMEMFUNPTR)
//#include "Invoke-UndefMemberCallMacos.h"
//
//    // Same treatment for ellipsises
//#include "Invoke-DefClassMacro.h"
//#define ISMEMFUNPTR_ELLIPSIS(CVRefNoExceptOpt)                      \
//  template<typename Ret, typename Arg0, typename... Types>          \
//  struct IsMemFunPtr<Ret (Arg0::*)(Types..., ...) CVRefNoExceptOpt> \
//  {                                                                 \
//    using BoolType = TrueType;                                      \
//    using ClassType = Arg0;                                         \
//    using GuideType = EnableIf<false>;                              \
//  };
//
//  // No entirely sure why this macro is called Class...
//  CLASS_DEFINE_CV_REF_NOEXCEPT(ISMEMFUNPTR_ELLIPSIS)
//#include "Invoke-UndefClassMacro.h"

  // Fuse MSVC's approach for capturing class type with the helper structs from TypeTraits-Pointer to avoid having to implement MSVC's whole _Is_memfunptr macro soup
  // These must be used with a RemoveCV_t or RemoveCVRef_t I think
*/

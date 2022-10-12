module;
#include "../Internal/Internal-Invoker.h"
export module autl.functional.invoke;

import autl.type_traits.invocable;
import autl.type_traits.isvoid;
import autl.utility.forward;

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

  /*
  * Invoke callable object. Result is implicitly converted to R if R not void, or discarded otherwise
  * Must pass IsInvocable_r_v to be considered
  */
  template<typename R, typename Callable, typename... Ts>
    requires IsInvocable_r_v<R, Callable, Ts...>
  constexpr R Invoke_r(Callable&& obj, Ts&&... args) noexcept(IsNoThrowInvocable_r_v<R, Callable, Ts...>)
  {
    if constexpr (IsVoid_v<R>)
    {
      Invoke(Forward<Callable>(obj), Forward<Ts>(args)...);
    }
    else
    {
      return Invoke(Forward<Callable>(obj), Forward<Ts>(args)...);
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

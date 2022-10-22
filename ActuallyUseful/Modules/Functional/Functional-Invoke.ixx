module;
export module autl.functional.invoke;

import "Internal-Invoker.h";
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

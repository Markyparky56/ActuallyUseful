module;
export module autl.concepts.invocable;

import autl.functional.invoke;
import autl.type_traits.invocable;
import autl.utility.forward;

export namespace autl
{
  /*
  * Specifies that the callable type F can be called with the set of Args using Invoke
  */
  template<typename F, typename... Args>
    concept Invocable = requires(F&& f, Args&&... args)
  {
      Invoke(Forward<F>(f), Forward<Args>(args)...);
  };
}

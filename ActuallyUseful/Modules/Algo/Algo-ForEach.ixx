module;
export module autl.algo.foreach;

import autl.functional.invoke;

export namespace autl
{
  /*
  * For-each item in input iterable, invoke callable 
  */
  template<typename InContainer, typename Callable>
  void ForEach(InContainer& input, Callable callable)
  {
    for (auto& val : input)
    {
      Invoke(callable, val);
    }
  }

  /*
  * For-each item, if the provided predicate evaluates to true, invoke callable
  */
  template<typename InContainer, typename Predicate, typename Callable>
  void ForEachIf(InContainer& input, Predicate predicate, Callable callable)
  {
    for (auto& val : input)
    {
      if (Invoke(predicate, val))
      {
        Invoke(callable, val);
      }
    }
  }
}

module;
export module autl.algo.noneof;

import autl.functional.invoke;

export namespace autl
{
  /*
  * Check each element of the given range, return false if any eval to true
  */
  template<typename RangeType>
  bool NoneOf(RangeType&& range)
  {
    for (const auto& element : range)
    {
      if (element)
      {
        return false;
      }
    }

    // None eval'd to true
    return true;
  }

  /*
  * Check each element of the given range, return false is any eval to true when projected by the given callable
  */
  template<typename RangeType, typename ProjectionCallable>
  bool NoneOf(RangeType&& range, ProjectionCallable proj)
  {
    for (const auto& element : range)
    {
      if (Invoke(proj, element))
      {
        return false;
      }
    }

    // None eval'd to true
    return true;
  }
}

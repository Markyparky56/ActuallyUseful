module;
export module autl.algo.allof;

import autl.functional.invoke;

export namespace autl
{
  /*
  * Check each element of the given range, return false if any eval to false
  */
  template<typename RangeType>
  bool AllOf(const RangeType& range)
  {
    for (const auto& element : range)
    {
      if (!element)
      {
        return false;
      }
    }

    // None eval'd to false
    return true;
  }

  /*
  * Check each element of the given range, return false is any eval to false when projected by the given callable
  */
  template<typename RangeType, typename ProjectionCallable>
  bool AllOf(const RangeType& range, ProjectionCallable proj)
  {
    for (const auto& element : range)
    {
      if (!Invoke(proj, element))
      {
        return false;
      }
    }

    // None eval'd to false
    return true;
  }
}

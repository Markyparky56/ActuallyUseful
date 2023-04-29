module;
export module autl.algo.anyof;

import autl.algo.noneof;
import autl.utility.move;
  
export namespace autl
{
  /*
  * Checks if any element in the given range evals to true
  */
  template<typename RangeType>
  bool AnyOf(RangeType&& range)
  {
    return !NoneOf(range);
  }

  /*
  * Check is any element, projected via the given callable, evals to true
  */
  template<typename RangeType, typename ProjectionCallable>
  bool AnyOf(RangeType&& range, ProjectionCallable proj)
  {
    return !NoneOf(range, Move(proj));
  }
}

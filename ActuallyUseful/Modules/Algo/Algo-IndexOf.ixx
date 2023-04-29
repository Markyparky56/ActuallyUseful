module;
export module autl.algo.indexof;

import autl.concepts.contiguousrange;
import autl.functional.invoke;
import autl.functional.operators;
import autl.utility.getdata;
import autl.utility.getnum;
import autl.utility.forward;
import autl.utility.move;

namespace autl
{
  // In theory these could be made better by requiring ProjectionCallable/PredicateCallable are invocable 
  // with the data type inside RangeType, but I don't see a clean way of getting the Type at the template level
  // without imposing some form of getter or overloading the function for different range types

  template<typename RangeType, typename ValueType, typename ProjectionCallable>
    requires ContiguousRange<RangeType> 
  auto IndexOfBy_Internal(RangeType&& range, const ValueType& value, ProjectionCallable proj)
  {
    auto num = GetNum(range);
    auto data = GetData(range);

    using it = decltype(num);
    for (it idx = 0; idx < num; ++idx)
    {
      // Project data at index and compare to value
      if (Invoke(proj, data[idx]) == value)
      {
        return idx;
      }
    }

    // -1 as INDEX_NONE
    return static_cast<decltype(num)>(-1);
  }

  template<typename RangeType, typename PredicateCallable>
    requires ContiguousRange<RangeType>
  auto IndexOfByPredicate_Internal(RangeType&& range, PredicateCallable pred)
  {
    auto num = GetNum(range);
    auto data = GetData(range);

    using it = decltype(num);
    for (it idx = 0; idx < num; ++idx)
    {
      // Pass data at index to predicate and return index if passes
      if (Invoke(pred, data[idx]))
      {
        return idx;
      }
    }

    // -1 as INDEX_NONE
    return static_cast<decltype(num)>(-1);
  }
}

export namespace autl
{
  /*
  * Returns the index of the first element in the range which is equal to the given value
  * Returns -1 (INDEX_NONE) if no match found
  */
  template<typename RangeType, typename ValueType>
    requires ContiguousRange<RangeType>
  auto IndexOf(RangeType&& range, const ValueType& value)
  {
    return IndexOfBy_Internal(Forward<RangeType>(range), value, Identity());
  }

  /*
  * Returns the index of the first element in the range which, when projected by the given callable, equals the given value
  * Returns -1 (INDEX_NONE) if no match found
  */
  template<typename RangeType, typename ValueType, typename ProjectionCallable>
    requires ContiguousRange<RangeType>
  auto IndexOfBy(RangeType&& range, const ValueType& value, ProjectionCallable proj)
  {
    return IndexOfBy_Internal(Forward<RangeType>(range), value, Move(proj));
  }

  /*
  * Returns the index of the first element in the range which passes the given predicate
  * Returns -1 (INDEX_NONE) if no match found
  */
  template<typename RangeType, typename PredicateCallable>
    requires ContiguousRange<RangeType>
  auto IndexOfByPredicate(RangeType&& range, PredicateCallable pred)
  {
    return IndexOfByPredicate_Internal(Forward<RangeType>(range), Move(pred));
  }
}

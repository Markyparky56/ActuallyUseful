module;
export module autl.algo.minelement;

import autl.type_traits.rangepointertype;
import autl.functional.invoke;
import autl.functional.operators;
import autl.utility.move;

namespace autl
{
  /*
  * Internal RangePointerType-based MinElement
  * Project each element with given projection callable then compare with given predicate callable
  */
  template<typename RangeType, typename ProjectionCallable, typename PredicateCallable>
  RangePointerType_t<RangeType> MinElementBy(RangeType& range, ProjectionCallable proj, PredicateCallable pred)
  {
    RangePointerType_t<RangeType> result = nullptr;

    for (auto& element : range)
    {     
      // Set result if not set, or predicate says element is less than current result
      if (!result || Invoke(pred, Invoke(proj, element), Invoke(proj, *result)))
      {
        // Take pointer to element
        result = &element;
      }
    }

    return result;
  }

  /*
  * Internal Iterator-based MinElement
  * Project each element with given projection callable then compare with given predicate callable
  */
  template<typename IteratorType, typename ProjectionCallable, typename PredicateCallable>
  IteratorType MinElementBy(IteratorType first, IteratorType last, ProjectionCallable proj, PredicateCallable pred)
  {
    // If only one element, that's our minimum
    if (first == last)
    {
      return first;
    }

    // Start at head of range
    IteratorType place = first;
    // First element is our starting minimum
    IteratorType result = first;

    // Compare next with current minimum
    while (++place != last)
    {
      if (Invoke(pred, Invoke(proj, *place), Invoke(proj, *result)))
      {
        // Replace result if new minimum
        result = place;
      }
    }

    return result;
  }
}

export namespace autl
{
  /*
  * Returns a pointer to the first minimum element in a range
  */
  template<typename RangeType>
  auto MinElement(RangeType& range) -> decltype(MinElementBy(range, Identity(), Less()))
  {
    return MinElementBy(range, Identity(), Less());
  }

  /*
  * Returns an iterator to the first minimum element in a range
  */
  template<typename IteratorType>
  auto MinElement(IteratorType first, IteratorType last) -> decltype(MinElementBy(Move(first), Move(last), Identity(), Less()))
  {
    return MinElementBy(Move(first), Move(last), Identity(), Less());
  }
}

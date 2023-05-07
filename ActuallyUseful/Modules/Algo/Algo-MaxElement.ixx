module;
export module autl.algo.maxelement;

import autl.concepts.supportsbegin;
import autl.type_traits.rangepointertype;
import autl.functional.invoke;
import autl.functional.operators;
import autl.utility.move;

namespace autl
{
  /*
  * Internal RangePointerType-based MaxElement
  * Project each element with given projection callable, then compare with given predicate callable
  */
  template<typename RangeType, typename ProjectionCallable, typename PredicateCallable>
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr RangePointerType_t<RangeType> MaxElementByInternal(RangeType& range, ProjectionCallable proj, PredicateCallable pred)
  {
    RangePointerType_t<RangeType> result = nullptr;

    for (auto& element : range)
    {
      // Set result if not set, or predicate says element is greater than current result
      if (!result || Invoke(pred, Invoke(proj, *result), Invoke(proj, element)))
      {
        // Take pointer to element
        result = &element;
      }
    }

    return result;
  }

  /*
  * Internal Iterator-based MaxElement
  * Project each element with given projection callable then compare with given predicate callable
  */
  template<typename IteratorType, typename ProjectionCallable, typename PredicateCallable>
  [[nodiscard]] constexpr IteratorType MaxElementByInternal(IteratorType first, IteratorType last, ProjectionCallable proj, PredicateCallable pred)
  {
    // If only one element, that's out maximum
    if (first == last)
    {
      return first;
    }

    // Start at head of range
    IteratorType place = first;
    // First element is our starting maximum
    IteratorType result = first;

    // Compare next with current maximum
    while (++place != last)
    {
      if (Invoke(pred, Invoke(proj, *result), Invoke(proj, *place)))
      {
        // Replace result if new maximum
        result = place;
      }
    }

    return result;
  }

}

export namespace autl
{
  /*
  * Returns a pointer to the first maximum element in a range
  * Element is expected to implement the < operator for comparison
  */
  template<typename RangeType>
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr auto MaxElement(RangeType& range) 
    -> decltype(MaxElementByInternal(range, Identity(), Less<>()))
  {
    return MaxElementByInternal(range, Identity(), Less<>());
  }

  /*
  * Returns a pointer to the first maximum element in a range, as determined by the given predicate callable
  */
  template<typename RangeType, typename PredicateCallable>
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr auto MaxElement(RangeType& range, PredicateCallable pred) 
    -> decltype(MaxElementByInternal(range, Identity(), Move(pred)))
  {
    return MaxElementByInternal(range, Identity(), Move(pred));
  }

  /*
  * Returns a pointer to the first maximum element in a range, projecting the element before comparison with the given projection callable
  * Element is expected to implement the < operator for comparison
  */
  template<typename RangeType, typename ProjectionCallable>
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr auto MaxElementBy(RangeType& range, ProjectionCallable proj) 
    -> decltype(MaxElementByInternal(range, Move(proj), Less<>()))
  {
    return MaxElementByInternal(range, Move(proj), Less<>());
  }

  /*
  * Returns a pointer to the maximum element in a range, as determined by the given predicate callable
  * projecting the element before comparison with the given projection callable
  */
  template<typename RangeType, typename ProjectionCallable, typename PredicateCallable>
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr auto MaxElementBy(RangeType& range, ProjectionCallable proj, PredicateCallable pred) 
    -> decltype(MaxElementByInternal(range, Move(proj), Move(pred)))
  {
    return MaxElementByInternal(range, Move(proj), Move(pred));
  }

  /*
  * Returns an iterator to the first maximum element in a range
  */
  template<typename IteratorType>
  [[nodiscard]] constexpr auto MaxElement(IteratorType first, IteratorType last) 
    -> decltype(MaxElementByInternal(first, last, Identity(), Less<>()))
  {
    return MaxElementByInternal(first, last, Identity(), Less<>());
  }

  /*
  * Returns an iterator to the first maximum element in a range, as determined by the given predicate callable
  */
  template<typename IteratorType, typename PredicateCallable>
  [[nodiscard]] constexpr auto MaxElement(IteratorType first, IteratorType last, PredicateCallable pred) 
    -> decltype(MaxElementByInternal(first, last, Identity(), Move(pred)))
  {
    return MaxElementByInternal(first, last, Identity(), Move(pred));
  }

  /*
  * Returns an iterator to the first maximum element in a range, projecting the element before comparison with the given projection callable
  * Element is expected to implement the < operator for comparison
  */
  template<typename IteratorType, typename ProjectionCallable>
  [[nodiscard]] constexpr auto MaxElementBy(IteratorType first, IteratorType last, ProjectionCallable proj) 
    -> decltype(MaxElementByInternal(first, last, Move(proj), Less<>()))
  {
    return MaxElementByInternal(first, last, Move(proj), Less<>());
  }

  /*
  * Returns an iterator the first maximum element in a range, as determined by the given predicate callable
  * projecting the element before comparison with the given projection callable
  */
  template<typename IteratorType, typename ProjectionCallable, typename PredicateCallable>
  [[nodiscard]] constexpr auto MaxElementBy(IteratorType first, IteratorType last, ProjectionCallable proj, PredicateCallable pred) 
    -> decltype(MaxElementByInternal(first, last, Move(proj), Move(pred)))
  {
    return MaxElementByInternal(first, last, Move(proj), Move(pred));
  }
}

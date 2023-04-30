module;
export module autl.algo.minelement;

import autl.concepts.supportsbegin;
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
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr RangePointerType_t<RangeType> MinElementByInternal(RangeType& range, ProjectionCallable proj, PredicateCallable pred)
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
  [[nodiscard]] constexpr IteratorType MinElementByInternal(IteratorType first, IteratorType last, ProjectionCallable proj, PredicateCallable pred)
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
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr auto MinElement(RangeType& range) -> decltype(MinElementByInternal(range, Identity(), Less<>()))
  {
    return MinElementByInternal(range, Identity(), Less<>());
  }

  /*
  * Returns a pointer to the first minimum element in a range, as determined by the given predicate callable
  */
  template<typename RangeType, typename PredicateCallable>
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr auto MinElement(RangeType& range, PredicateCallable pred) -> decltype(MinElementByInternal(range, Identity(), Move(pred)))
  {
    return MinElementByInternal(range, Identity(), Move(pred));
  }

  /*
  * Returns a pointer to the first minimum element in a range, projecting the element before comparison with the given projection callable
  */
  template<typename RangeType, typename ProjectionCallable>
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr auto MinElementBy(RangeType& range, ProjectionCallable proj) -> decltype(MinElementByInternal(range, Move(proj), Less<>()))
  {
    return MinElementByInternal(range, Move(proj), Less<>());
  }

  /*
  * Returns a pointer to the first minimum element in a range, as determined by the given predicate callable
  * projecting the element before comparison with the given projection callable
  */
  template<typename RangeType, typename ProjectionCallable, typename PredicateCallable>
    requires SupportsBegin<RangeType>
  [[nodiscard]] constexpr auto MinElementBy(RangeType& range, ProjectionCallable proj, PredicateCallable pred) -> decltype(MinElementByInternal(range, Move(proj), Move(pred)))
  {
    return MinElementByInternal(range, Move(proj), Move(pred));
  }

  /*
  * Returns an iterator to the first minimum element in a range
  */
  template<typename IteratorType>
  [[nodiscard]] constexpr auto MinElement(IteratorType first, IteratorType last) -> decltype(MinElementByInternal(Move(first), Move(last), Identity(), Less<>()))
  {
    return MinElementByInternal(Move(first), Move(last), Identity(), Less<>());
  }

  /*
  * Returns an iterator to the first minimum element in a range, as determined by the given predicate callable
  */
  template<typename IteratorType, typename PredicateCallable>
  [[nodiscard]] constexpr auto MinElement(IteratorType first, IteratorType last, PredicateCallable pred) -> decltype(MinElementByInternal(Move(first), Move(last), Identity(), Move(pred)))
  {
    return MinElementByInternal(Move(first), Move(last), Identity(), Move(pred));
  }

  /*
  * Returns an iterator to the first minimum element in a range, projecting the element before comparison with the given projection callable
  */
  template<typename IteratorType, typename ProjectionCallable>
  [[nodiscard]] constexpr auto MinElementBy(IteratorType first, IteratorType last, ProjectionCallable proj) -> decltype(MinElementByInternal(Move(first), Move(last), Move(proj), Less<>()))
  {
    return MinElementByInternal(Move(first), Move(last), Move(proj), Less<>());
  }

  /*
  * Returns an iterator to the first minimum element in a range, as determined by the given predicate callable
  * projecting the element before comparison with the given projection callable
  */
  template<typename IteratorType, typename ProjectionCallable, typename PredicateCallable>
  [[nodiscard]] constexpr auto MinElementBy(IteratorType first, IteratorType last, ProjectionCallable proj, PredicateCallable pred) -> decltype(MinElementByInternal(Move(first), Move(last), Move(proj), Move(pred)))
  {
    return MinElementByInternal(Move(first), Move(last), Move(proj), Move(pred));
  }
}

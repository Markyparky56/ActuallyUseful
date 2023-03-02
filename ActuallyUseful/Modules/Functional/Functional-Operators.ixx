module;
export module autl.functional.operators;

import autl.concepts.equalitycomparable;
import autl.utility.forward;

export namespace autl
{
  /*
  * 
  */
  struct EqualTo
  {
    template<typename A, typename B>
      requires EqualityComparableWith<A, B>
    [[nodiscard]] constexpr bool operator()(A&& lhs, B&& rhs) const noexcept(noexcept(
      static_cast<bool>(Forward<A>(lhs) == Forward<B>(rhs))))
    {
      return static_cast<bool>(Forward<A>(lhs) == Forward<B>(rhs));
    }

    using IsTransparent = void;
  };

}

module;
export module autl.utility.swap;

import autl.type_traits.isconstructible;
import autl.type_traits.isassignable;
import autl.type_traits.isswappable;
import autl.type_traits.enableif;
import autl.types.std;
import autl.utility.move;

export namespace autl
{
  /*
  * Swap the values a and b provided T is move constructible and move assignable
  * Only enabled for types that are move constructible and move assignable
  * NoThrow if T is 
  * - NoThrowMoveConstructible
  * - NoThrowMoveAssignable
  */
  template<typename T, EnableIf_t<IsMoveConstructible_v<T> && IsMoveAssignable_v<T>, int> = 0>
  constexpr void Swap(T& a, T& b) noexcept(IsNoThrowMoveConstructible_v<T> && IsNoThrowMoveAssignable_v<T>)
  {
    T temp(Move(a));
    a    = Move(b);
    b    = Move(temp);
  }

  /*
  * Swap the arrays a and b
  */
  template<typename T, size_t N, EnableIf_t<IsSwappable<T>::Value, int> = 0>
  constexpr void Swap(T (&left)[N], T (&right)[N]) noexcept(IsNoThrowSwappable<T>::Value)
  {
    for (size_t i = 0; i != N; ++i)
    {
      Swap(left[i], right[i]);
    }
  }
}

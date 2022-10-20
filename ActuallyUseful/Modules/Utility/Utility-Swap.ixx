module;
#include <string.h> // For memcpy until replaced
export module autl.utility.swap;

import autl.type_traits.isconstructible;
import autl.type_traits.isassignable;
import autl.type_traits.isswappable;
import autl.type_traits.enableif;
import autl.type_traits.integralconstant;
import autl.type_traits.logical;
import autl.type_traits.isenum;
import autl.type_traits.pointer;
import autl.type_traits.isarithmetic;
import autl.types.std;
import autl.utility.move;
import autl.utility.alignedbytes;

namespace autl
{
  /*
  * Types small enough to fit in a register can be quickly swapped by-value, 
  * for larger objects a bitwise (memcpy) swap can be used 
  */
  template<typename T>
  struct UseBitwiseSwap : BoolConstant<!OR_v<IsEnum<T>, IsPointer<T>, IsArithmetic<T>>> {};
  template<typename T>
  constexpr inline bool UseBitwiseSwap_v = UseBitwiseSwap<T>::Value;
}

export namespace autl
{
  /*
  * Swap the values a and b provided T is move constructible and move assignable
  * Only enabled for types that are move constructible and move assignable
  * NoThrow if T is 
  * - NoThrowMoveConstructible
  * - NoThrowMoveAssignable
  */
  template<typename T> requires(UseBitwiseSwap_v<T> && IsMoveConstructible_v<T>&& IsMoveAssignable_v<T>)
  constexpr void Swap(T& a, T& b) noexcept(IsNoThrowMoveConstructible_v<T>&& IsNoThrowMoveAssignable_v<T>)
  {
    if (/*likely*/(&a != &b))
    {
      TypeCompatibleBytes<T> temp;
      memcpy(&temp, &a, sizeof(T));
      memcpy(&a, &b, sizeof(T));
      memcpy(&b, &temp, sizeof(T));
    }
  }
  //template<typename T, EnableIf_t<!UseBitWiseSwap_v<T> && IsMoveConstructible_v<T> && IsMoveAssignable_v<T>, int> = 0>
  template<typename T> requires(!UseBitwiseSwap_v<T> && IsMoveConstructible_v<T> && IsMoveAssignable_v<T>)
  constexpr void Swap(T& a, T& b) noexcept(IsNoThrowMoveConstructible_v<T> && IsNoThrowMoveAssignable_v<T>)
  {
    T temp(Move(a));
    a    = Move(b);
    b    = Move(temp);
  }

  /*
  * Swap the arrays a and b
  */
  template<typename T, size_t N> requires(IsSwappable<T>::Value)
  constexpr void Swap(T (&left)[N], T (&right)[N]) noexcept(IsNoThrowSwappable<T>::Value)
  {
    for (size_t i = 0; i != N; ++i)
    {
      Swap(left[i], right[i]);
    }
  }
}

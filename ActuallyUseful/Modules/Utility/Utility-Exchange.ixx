module;
export module autl.utility.exchange;

import autl.utility.move;
import autl.utility.forward;
import autl.type_traits.isconstructible;
import autl.type_traits.isassignable;

export namespace autl
{
  /*
  * Replace the value of obj with newValue and returns the old value of obj
  */
  template<typename T, typename U=T>
  constexpr T Exchange(T& obj, U&& newValue) noexcept(IsNoThrowMoveConstructible_v<T>&& IsNoThrowAssignable_v<T&, U>)
  {
    T oldValue = Move(obj);
    obj = Forward<U>(newValue);
    return oldValue;
  }
}

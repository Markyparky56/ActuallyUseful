module;
export module autl.utility.move;

import autl.type_traits.logical;
import autl.type_traits.isconstructible;
import autl.type_traits.reference;

export namespace autl
{
  /*
  * Indicate that an object T may be "moved from"
  * Produces an xvalue expression
  * Equivalent to static_cast<T&&>(arg)
  */
  template<typename T>
  [[nodiscard]] constexpr RemoveReference_t<T>&& Move(T&& arg) noexcept
  {
    return static_cast<RemoveReference_t<T>&&>(arg);
  }

  /*
  * Obtain an rvalue reference to arg if its move constructor does not throw exceptions or if there is no copy constructor (move-only type)
  * Otherwise obtains an lvalue reference to arg
  * Use to combine move semantics with strong exception guarantee
  */
  template<typename T>
  [[nodiscard]] constexpr Conditional_t<!IsNoThrowMoveConstructible_v<T>&& IsCopyConstructible_v<T>, const T&, T&&> MoveIfNoExcept(T& arg) noexcept
  {
    return Move(arg);
  }

  /*
  * Stricter instance of Move which asserts if passed a value which will not benefit from move semantics
  */
  template<typename T>
  [[nodiscard]] constexpr RemoveReference_t<T>&& MoveStrict(T&& arg) noexcept
  {
    static_assert(IsLValueReference_v<T>, "Move called on an rvalue");
    static_assert(!IsSame_v<T&, const T&>, "Move called on a const object");

    return static_cast<RemoveReference_t<T>&&>(arg);
  }
}

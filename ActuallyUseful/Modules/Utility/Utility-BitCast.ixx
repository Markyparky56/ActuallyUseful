module;
export module autl.utility.bitcast;

import autl.type_traits.istrivial;
import autl.type_traits.enableif;

export namespace autl
{
  template<typename To, typename From> 
    requires(sizeof(To) == sizeof(From) && IsTriviallyCopyable_v<To> && IsTriviallyCopyable_v<From>)
  [[nodiscard]] constexpr To BitCast(const From& from) noexcept
  {
    return __builtin_bit_cast(To, from);
  }
}

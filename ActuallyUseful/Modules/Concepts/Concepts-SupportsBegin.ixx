module;
export module autl.concepts.supportsbegin;

import autl.utility.declval;
import autl.utility.begin;

export namespace autl
{
  /*
  * Require the given range to support autl::Begin
  */
  template<typename RangeType>
  concept SupportsBegin = requires
  {
    { Begin(Declval<RangeType&>()) };
  };
}

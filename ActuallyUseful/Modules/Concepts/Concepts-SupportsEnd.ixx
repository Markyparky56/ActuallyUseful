module;
export module autl.concepts.supportsend;

import autl.utility.declval;
import autl.utility.end;

export namespace autl
{
  /*
  * Require the given range to support autl::End
  */
  template<typename RangeType>
  concept SupportsEnd = requires
  {
    { End(Declval<RangeType&>()) };
  };
}

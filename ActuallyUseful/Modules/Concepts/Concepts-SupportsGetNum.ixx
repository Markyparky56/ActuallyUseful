module;
export module autl.concepts.supportsgetnum;

import autl.utility.declval;
import autl.utility.getnum;

export namespace autl
{
  /*
  * Require the given range to support autl::GetNum
  */
  template<typename RangeType>
  concept SupportsGetNum = requires
  {
    { GetNum(Declval<RangeType&>()) };
  };
}

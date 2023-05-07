module;
export module autl.concepts.supportsgetdata;

import autl.utility.declval;
import autl.utility.getdata;

export namespace autl
{
  /*
  * Require the given range to support autl::GetNum
  */
  template<typename RangeType>
  concept SupportsGetData = requires
  {
    { GetData(Declval<RangeType&>()) };
  };
}

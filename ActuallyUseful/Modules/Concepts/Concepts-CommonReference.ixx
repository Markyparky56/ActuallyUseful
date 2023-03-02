module;
export module autl.concepts.commonreference;

import autl.concepts.sameas;
import autl.type_traits.commonreference;
import autl.concepts.convertibleto;

export namespace autl
{
  /*
  * 
  */
  template<typename A, typename B>
  concept CommonReferenceWith =
    SameAs<CommonReference_t<A, B>, CommonReference_t<B, A>>
    && ConvertibleTo<A, CommonReference_t<A, B>>
    && ConvertibleTo<B, CommonReference_t<A, B>>;
}

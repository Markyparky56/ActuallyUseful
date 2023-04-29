module;
export module autl.concepts.commonwith;

import autl.concepts.sameas;
import autl.concepts.commonreference;
import autl.type_traits.commontype;
import autl.type_traits.reference;
import autl.utility.declval;

export namespace autl
{
  /*
  * Specifies that A and B share a common type to which both can be converted
  */
  template<typename A, typename B>
  concept CommonWith = SameAs<CommonType_t<A, B>, CommonType_t<B, A>>
    && requires {
      static_cast<CommonType_t<A, B>>(Declval<A>());
      static_cast<CommonType_t<A, B>>(Declval<B>());
    }
    && CommonReferenceWith<AddLValueReference_t<const A>, AddLValueReference_t<const B>>
    && CommonReferenceWith<AddLValueReference_t<CommonType_t<A, B>>,
                           CommonType_t<AddLValueReference_t<const A>, AddLValueReference_t<const B>>>;
}

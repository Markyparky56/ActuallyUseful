module;
export module autl.concepts.sameas;

import autl.type_traits.logical;

namespace autl
{
  // Must be a distinct concept to provide symmetric subsumption for SameAs
  template<typename A, typename B> concept SameHelper = IsSame_v<A, B>;
}

export namespace autl
{
  /*
  * Satisfied if and only if T and U are of the same type
  */
  template<typename A, typename B> concept SameAs = SameHelper<A, B> && SameHelper<B, A>;
}

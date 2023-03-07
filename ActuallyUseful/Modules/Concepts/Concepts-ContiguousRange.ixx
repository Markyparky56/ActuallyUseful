module;
export module autl.concepts.contiguousrange;

import autl.type_traits.iscontiguous;

export namespace autl
{
  /*
  * Specifies that the given container must be contiguous
  * Must satisfy IsContiguous
  */
  template<typename T> concept ContiguousRange = IsContiguous_v<T>;
}
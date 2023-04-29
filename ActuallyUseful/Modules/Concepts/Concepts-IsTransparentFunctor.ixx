module;
export module autl.concepts.istransparent;

import autl.functional.istransparent;

export namespace autl
{
  /*
  * Specifies that the function object must be a transparent function object
  * That is, it specifies a member of IsTransparent of arbitrary type
  */
  template<typename T>
  concept IsTransparentFunctor = IsTransparent_v<T>;
}

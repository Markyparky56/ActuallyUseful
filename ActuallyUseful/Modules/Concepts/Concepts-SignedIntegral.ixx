module;
export module autl.concepts.signedintegral;

import autl.type_traits.isintegral;
import autl.type_traits.issigned;

export namespace autl
{
  template<typename T> concept SignedIntegral = IsIntegral_v<T> && IsSigned_v<T>;
}
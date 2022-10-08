module;
export module autl.concepts.unsignedintegral;

import autl.type_traits.isintegral;
import autl.type_traits.issigned;

export namespace autl
{
  template<typename T> concept UnsignedIntegral = IsIntegral_v<T> && !IsSigned_v<T>;
}
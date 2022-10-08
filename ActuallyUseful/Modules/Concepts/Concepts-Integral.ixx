module;
export module autl.concepts.integral;

import autl.type_traits.isintegral;

export namespace autl
{
  template<typename T> concept Integral = IsIntegral_v<T>;
  template<typename T> concept NonIntegral = !IsIntegral_v<T>;
}

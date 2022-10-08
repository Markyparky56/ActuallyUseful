module;
export module autl.concepts.arithmetic;

import autl.type_traits.isarithmetic;

export namespace autl
{
  template<typename T> concept Arithemetic = IsArithmetic_v<T>;
  template<typename T> concept NonArithemetic = !IsArithmetic_v<T>;
}

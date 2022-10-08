module;
export module autl.concepts.floatingpoint;

import autl.type_traits.isfloatingpoint;

export namespace autl
{
  template<typename T> concept FloatingPoint = IsFloatingPoint_v<T>;
  template<typename T> concept NonFloatingPoint = !IsFloatingPoint_v<T>;
}

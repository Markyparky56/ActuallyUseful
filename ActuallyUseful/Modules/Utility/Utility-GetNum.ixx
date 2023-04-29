module;
#include <initializer_list>
export module autl.utility.getnum;

import autl.concepts.contiguousrange;
import autl.types.std;

export namespace autl
{
  /*
  * Returns the number of items in a contiguous container
  */
  template<typename T>
    requires ContiguousRange<T>
  constexpr auto GetNum(T&& container) -> decltype(container.GetNum())
  {
    return container.GetNum();
  }

  /*
  * Returns the number of items in a contiguous c-array
  */
  template<typename T, size_t N> constexpr       size_t GetNum(      T(& container)[N]) { return N; }
  template<typename T, size_t N> constexpr       size_t GetNum(      T(&&container)[N]) { return N; }
  template<typename T, size_t N> constexpr const size_t GetNum(const T(& container)[N]) { return N; }
  template<typename T, size_t N> constexpr const size_t GetNum(const T(&&container)[N]) { return N; }

  /*
  * Returns the number of items in an initializer list
  */
  template<typename T> constexpr const size_t GetNum(std::initializer_list<T> list) { return list.size(); }
}

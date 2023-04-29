module;
#include <initializer_list>
export module autl.utility.getdata;

import autl.concepts.contiguousrange;
import autl.type_traits.core;
import autl.types.std;

export namespace autl
{
  /*
  * Returns the data pointer of a contiguous container
  */
  template<typename T>
    requires ContiguousRange<T>
  constexpr auto GetData(T&& container) -> decltype(container.GetData())
  {
    return container.GetData();
  }

  /*
  * Returns the data pointer of a contiguous c-array
  */
  template<typename T, size_t N> constexpr T*       GetData(      T(& container)[N]) { return container; }
  template<typename T, size_t N> constexpr T*       GetData(      T(&&container)[N]) { return container; }
  template<typename T, size_t N> constexpr const T* GetData(const T(& container)[N]) { return container; }
  template<typename T, size_t N> constexpr const T* GetData(const T(&&container)[N]) { return container; }

  /*
  * Returns the data pointer of an initializer list
  */
  template<typename T> constexpr const T* GetData(std::initializer_list<T> list) { return list.begin(); }
}

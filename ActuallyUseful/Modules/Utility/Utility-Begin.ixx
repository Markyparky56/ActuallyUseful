module;
export module autl.utility.begin;

import autl.types.std;

namespace autl
{
  /*
  * Require the given container type to implement ::begin()
  */
  template<typename ContainerType>
  concept ImplementsBeginMember = requires(ContainerType t)
  {
    { t.begin() };
  };
}

export namespace autl
{
  /*
  * Return an iterator to the beginning of the given range
  */
  template<typename ContainerType>
    requires ImplementsBeginMember<ContainerType>
  [[nodiscard]] constexpr auto Begin(ContainerType& container) 
    noexcept(noexcept(container.begin())) -> decltype(container.begin())
  {
    return container.begin();
  }
  template<typename ContainerType>
    requires ImplementsBeginMember<ContainerType>
  [[nodiscard]] constexpr auto Begin(const ContainerType& container) 
    noexcept(noexcept(container.begin())) -> decltype(container.begin())
  {
    return container.begin();
  }

  /*
  * Return an explicitly const iterator to the beginning of the given range
  */
  template<typename ContainerType>
    requires ImplementsBeginMember<ContainerType>
  [[nodiscard]] constexpr auto CBegin(const ContainerType& container)
    noexcept(noexcept(Begin(container))) -> decltype(container)
  {
    return Begin(container);
  }

  /*
  * Return the head of the given array
  */
  template<typename T, size_t N>
  [[nodiscard]] constexpr T* Begin(T(&arr)[N]) noexcept { return arr; }
}

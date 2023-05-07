module;
export module autl.utility.end;

import autl.types.std;

namespace autl
{
  /*
  * Require the given container type to implement ::end()
  */
  template<typename ContainerType>
  concept ImplementsEndMember = requires(ContainerType t)
  {
    { t.end() };
  };
}

export namespace autl
{
  /*
  * Return an iterator to the end of the given range
  */
  template<typename ContainerType>
    requires ImplementsEndMember<ContainerType>
  [[nodiscard]] constexpr auto End(ContainerType& container)
    noexcept(noexcept(container.end())) -> decltype(container.end())
  {
    return container.end();
  }
  template<typename ContainerType>
    requires ImplementsEndMember<ContainerType>
  [[nodiscard]] constexpr auto End(const ContainerType& container)
    noexcept(noexcept(container.end())) -> decltype(container.end())
  {
    return container.end();
  }

  /*
  * Return an explicitly const iterator to the end of the given range
  */
  template<typename ContainerType>
    requires ImplementsEndMember<ContainerType>
  [[nodiscard]] constexpr auto CEnd(const ContainerType& container)
    noexcept(noexcept(End(container))) -> decltype(container)
  {
    return End(container);
  }

  /*
  * Return the end of the given array
  */
  template<typename T, size_t N>
  [[nodiscard]] constexpr T* End(T(&arr)[N]) noexcept { return arr + N; }
}

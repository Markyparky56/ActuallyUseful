module;
export module autl.memory.addressof;

export namespace autl
{
  /*
  * Obtain the actual address of the object or function arg, even in the presence of overloaded operator&
  */
  template<typename T>
  [[nodiscard]] constexpr T* AddressOf(T& val) noexcept
  {
    // constexpr AddressOf requires a builtin, all >C++17 supporting compilers should have one
    return __builtin_addressof(val);
  }

  // Deleted to prevent taking the address of constant rvalues
  template<typename T>
  const T* AddressOf(const T&&) = delete;
}

// Technically, this would probably work as a "replacement" for std::initializer_list but due to special-case
// rules involving auto, std::initializer_list cannot be replaced easily/at all
//module;
//export module autl.initializerlist;
//
//import autl.types.std;
//
//export namespace autl
//{
//  /*
//  *
//  */
//  template<typename T>
//  class InitializerList
//  {
//  public:
//    // I believe these defines are required for compiler-purposes?
//    using value_type = T;
//    using reference = const T&;
//    using const_reference = const T&;
//    using size_type = size_t;
//    using iterator = const T*;
//    using const_iterator = const T*;
//
//    constexpr InitializerList() noexcept
//      : Data(nullptr)
//      , Size(0)
//    {}
//
//    constexpr InitializerList(const T* firstArg, size_t size) noexcept
//      : Data(firstArg)
//      , Size(size)
//    {}
//
//    // Return pointer to beginning of list
//    [[nodiscard]] constexpr const T* Begin() const noexcept { return Data; }
//    // lower-case required for for-each integration
//    [[nodiscard]] constexpr const T* begin() const noexcept { return Data; }
//
//    // Return pointer to one the past the end of the list
//    [[nodiscard]] constexpr const T* End() const noexcept { return Data + Size; }
//    // lower-case required for for-each integration
//    [[nodiscard]] constexpr const T* end() const noexcept
//    {
//      return Data + Size;
//    }
//
//    // Return size of list
//    [[nodiscard]] constexpr size_t GetSize() const noexcept
//    {
//      return Size;
//    }
//
//  private:
//    const T* Data;
//    size_t Size;
//  };
//
//  // Free function Begin
//  template<typename T>
//  [[nodiscard]] constexpr const T* Begin(InitializerList<T> list) noexcept
//  {
//    return list.Begin();
//  }
//
//  // Free function End
//  template<typename T>
//  [[nodiscard]] constexpr const T* End(InitializerList<T> list) noexcept
//  {
//    return list.End();
//  }
//}

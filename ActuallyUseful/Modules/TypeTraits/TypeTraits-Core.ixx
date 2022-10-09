module;
export module autl.type_traits.core;

export namespace autl
{
  /*
  * Provide type unmodified
  */
  template<typename T> struct TypeIdentity { using Type = T; };

  /*
  * Helper to access ::Type of TypeIdentity
  */
  template<typename T> using TypeIdentity_t = typename TypeIdentity<T>::Type;

  /*
  * False value attached to a dependent name (for static_assert)
  * Non-standard, borrowed from MSVC STL
  */
  template<typename> inline constexpr bool AlwaysFalse = false;
}

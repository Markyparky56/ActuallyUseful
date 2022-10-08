module;
export module autl.type_traits.core;

export namespace autl
{
  /*
  * Provide type unmodified
  */
  export template<typename T> struct TypeIdentity { using Type = T; };

  /*
  * void utility metafunction
  */
  export template<typename...> using Void_t = void;

  /*
  * False value attached to a dependent name (for static_assert)
  * Non-standard, borrowed from MSVC STL
  */
  export template<typename> inline constexpr bool AlwaysFalse = false;

}

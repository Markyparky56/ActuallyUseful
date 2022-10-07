module;
export module autl.type_traits.types;

/*
* ActuallyUseful Type Traits helpers
*/
export namespace autl
{
  /*
  * Provide type unmodified
  */
  template<typename T> struct TypeIdentity { using Type = T; };

  /*
  * void utility metafunction
  */
  template<typename...> using Void_t = void;

  /*
  * False value attached to a dependent name (for static_assert)
  */
  template<typename> inline constexpr bool AlwaysFalse = false;
}
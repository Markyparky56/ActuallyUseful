module;
export module autl.type_traits.enableif;

export namespace autl
{
  /*
  * If B is true, EnableIf has a public member Type equal to T, otherwise there is no member
  * Used to conditionally remove functions from the candiate set based on type traits
  * Precursor/Alternative to concepts
  */
  template<bool B, typename T = void> struct EnableIf {};
  template<typename T> struct EnableIf<true, T> { using Type = T; };

  /*
  * Helper to access ::Type of EnableIf
  */
  template<bool B, typename T = void> using EnableIf_t = typename EnableIf<B, T>::Type;
}

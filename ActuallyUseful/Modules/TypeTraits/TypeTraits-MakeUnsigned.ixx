module;
export module autl.type_traits.makeunsigned;

import autl.types.std;
import autl.type_traits.logical;
import autl.type_traits.isintegral;
import autl.type_traits.isenum;
import autl.type_traits.constvolatile;

export namespace autl
{
  // Select type by size
  template<size_t>
  struct MakeUnsigned_SizedHelper;

  // Char/Byte
  template<>
  struct MakeUnsigned_SizedHelper<1>
  {
    template<typename> using Apply = unsigned char;
  };

  // Short
  template<>
  struct MakeUnsigned_SizedHelper<2>
  {
    template<typename> using Apply = unsigned short;
  };

  // Long/Int
  template<>
  struct MakeUnsigned_SizedHelper<4>
  {
    template<typename T>
    using Apply = typename Selector<IsSame_v<T, long> || IsSame_v<T, signed long>>::template Apply<unsigned long, unsigned int>;
  };

  // Long Long
  template<>
  struct MakeUnsigned_SizedHelper<8>
  {
    template<typename> using Apply = unsigned long long;
  };

  template<typename T> using MakeUnsignedHelper = typename MakeUnsigned_SizedHelper<sizeof(T)>::template Apply<T>;
}

export namespace autl
{
  /*
  * If T is an integral (except bool) or enum, provide the unsigned version it as ::Type
  * Preserves cv-qualifiers
  */
  template<typename T>
  struct MakeUnsigned
  {
    static_assert(IsNonBoolIntegral_v<T> || IsEnum_v<T>, "MakeUnsigned cannot be used with bool types");

    using Type = TransferCV_t<T, MakeUnsignedHelper<RemoveCV_t<T>>>;
  };

  /*
  * Helper to access ::Type of MakeUnsigned
  */
  template<typename T> using MakeUnsigned_t = typename MakeUnsigned<T>::Type;
}

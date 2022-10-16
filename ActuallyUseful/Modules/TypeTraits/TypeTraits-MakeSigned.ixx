module;
export module autl.type_traits.makesigned;

import autl.types.std;
import autl.type_traits.logical;
import autl.type_traits.isintegral;
import autl.type_traits.isenum;
import autl.type_traits.constvolatile;

export namespace autl
{
  // Select type by size
  template<size_t>
  struct MakeSigned_SizedHelper;

  // Char/Byte
  template<>
  struct MakeSigned_SizedHelper<1>
  {
    template<typename> using Apply = signed char;
  };

  // Short
  template<>
  struct MakeSigned_SizedHelper<2>
  {
    template<typename> using Apply = short;
  };

  // Long/Int
  template<>
  struct MakeSigned_SizedHelper<4>
  {
    template<typename T>
    using Apply = typename Selector<IsSame_v<T, long> || IsSame_v<T, unsigned long>>::template Apply<long, int>;
  };

  // Long Long
  template<>
  struct MakeSigned_SizedHelper<8>
  {
    template<typename> using Apply = long long;
  };

  template<typename T> using MakeSignedHelper = typename MakeSigned_SizedHelper<sizeof(T)>::template Apply<T>;
}

export namespace autl
{
  /*
  * If T is an integral (except bool) or enum, provide the signed version of it as ::Type
  * Preserves cv-qualifiers
  */
  template<typename T>
  struct MakeSigned
  {
    static_assert(IsNonBoolIntegral_v<T> || IsEnum_v<T>, "MakeSigned cannot be used with bool types");

    using Type = TransferCV_t<T, MakeSignedHelper<RemoveCV_t<T>>>;
  };

  /*
  * Helper to access ::Type of MakeSigned
  */
  template<typename T> using MakeSigned_t = typename MakeSigned<T>::Type;
}
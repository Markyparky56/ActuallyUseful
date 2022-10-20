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
  template<typename T, size_t>
  struct MakeSigned_SizedHelper;

  // Char/Byte
  template<typename T>
  struct MakeSigned_SizedHelper<T, 1>
  {
    using Type = signed char;
  };

  // Short
  template<typename T>
  struct MakeSigned_SizedHelper<T, 2>
  {
    using Type = short;
  };

  // Long/Int
  template<typename T>
  struct MakeSigned_SizedHelper<T, 4>
  {
    // NOTE: This make need #if-ing if compiling with clang/gcc where long might be 64bits? Sizeof might handle that though?
    using Type = typename Conditional_t<IsSame_v<T, long> || IsSame_v<T, unsigned long>, long, int>;
  };

  // Long Long
  template<typename T>
  struct MakeSigned_SizedHelper<T, 8>
  {
    using Type = long long;
  };

  template<typename T> using MakeSignedHelper = typename MakeSigned_SizedHelper<T, sizeof(T)>::Type;
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
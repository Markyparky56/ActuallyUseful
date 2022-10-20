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
  template<typename T, size_t>
  struct MakeUnsigned_SizedHelper;

  // Char/Byte
  template<typename T>
  struct MakeUnsigned_SizedHelper<T, 1>
  {
    using Type = unsigned char;
  };

  // Short
  template<typename T>
  struct MakeUnsigned_SizedHelper<T, 2>
  {
    using Type = unsigned short;
  };

  // Long/Int
  template<typename T>
  struct MakeUnsigned_SizedHelper<T, 4>
  {
    using Type = typename Conditional_t<IsSame_v<T, long> || IsSame_v<T, signed long>, unsigned long, unsigned int>;
  };

  // Long Long
  template<typename T>
  struct MakeUnsigned_SizedHelper<T, 8>
  {
    using Type = unsigned long long;
  };

  template<typename T> using MakeUnsignedHelper = typename MakeUnsigned_SizedHelper<T, sizeof(T)>::Type;
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

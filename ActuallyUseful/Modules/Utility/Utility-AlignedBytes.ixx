module;
export module autl.utility.alignedbytes;

import autl.utility.bitcast;
import autl.types.byte;
import autl.types.std;
import autl.types.arithmetic;

export namespace autl
{
  /*
  * A wrapped byte array with compile-time alignment
  * Accepted alignments: 1, 2, 4, 8, 16, 32, 64
  */
  template<size_t Size, uint8 Alignment> requires(Alignment>0 && Alignment<=64) 
  struct AlignedBytes
  {
    struct alignas(Alignment) AlignedBuff
    {
      byte Buffer[Size];
    };
    AlignedBuff Bytes;
  };

  /*
  * A wrapped byte array with compile-time alignment, sized to T
  */
  template<typename T>
  struct TypeCompatibleBytes : public AlignedBytes<sizeof(T), alignof(T)>
  {
    [[nodiscard]] constexpr T* GetTypedPtr() noexcept
    {
      return BitCast<T*>(this);
    }
    [[nodiscard]] constexpr const T* GetTypedPtr() const noexcept
    {
      return BitCast<const T*>(this);
    }
  };
}
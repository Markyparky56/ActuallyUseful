module;
export module autl.type_traits.constvolatile;

import autl.type_traits.integralconstant;

/*
* ActuallyUseful Type Traits
* 
* AddConst
* AddConst_t
* RemoveConst
* RemoveConst_t
* 
* AddVolatile
* AddVolatile_t
* RemoveVolatile
* RemoveVolatile_t
* 
* AddConstVolatile
* AddConstVolatile_t
* RemoveCV
* RemoveCV_t 
*/
export namespace autl
{
  /*
  * Determines if given type is const
  */
  template<typename T> struct IsConst : FalseType {};
  template<typename T> struct IsConst<const T> : TrueType {};

  /*
  * Helper to access ::Value of IsConst
  */
  template<typename T> inline constexpr bool IsConst_v = IsConst<T>::Value;

  /*
  * Add const to a given type
  */
  template<typename T> struct AddConst { using Type = const T; };

  /*
  * Helper to access ::Type of AddConst
  */
  template<typename T> using AddConst_t = typename AddConst<T>::Type;

  /*
  * Remove the topmost const, underlying type available via ::Type
  */
  template<typename T> struct RemoveConst { using Type = T; };
  template<typename T> struct RemoveConst<const T> { using Type = T; };

  /*
  * Helper to access ::Type of RemoveConst
  */
  template<typename T> using RemoveConst_t = typename RemoveConst<T>::Type;

  /*
  * Determines if given type is volatile
  */
  template<typename T> struct IsVolatile : FalseType {};
  template<typename T> struct IsVolatile<volatile T> : TrueType {};

  /*
  * Helper to access ::Value of IsVolatile
  */
  template<typename T> inline constexpr bool IsVolatile_v = IsVolatile<T>::Value;

  /*
  * Add Volatile to a given type  
  */
  template<typename T> struct AddVolatile { using Type = volatile T; };

  /*
  * Helper to access ::Type of AddVolatile
  */
  template<typename T> using AddVolatile_t = typename AddVolatile<T>::Type;

  /*
  * Remove the topmost volatile, underlying type available via ::Type
  */
  template<typename T> struct RemoveVolatile { using Type = T; };
  template<typename T> struct RemoveVolatile<volatile T> { using Type = T; };

  /*
  * Helper to access ::Type of RemoveVolatile
  */
  template<typename T> using RemoveVolatile_t = typename RemoveVolatile<T>::Type;

  /*
  * Add Const Volatile to a given type
  */
  template<typename T> struct AddCV { using Type = const volatile T; };

  /*
  * Helper to access ::Type of AddCV
  */
  template<typename T> using AddCV_t = typename AddCV<T>::Type;

  /*
  * Remove the topmost const or topmost volatile, or both if present
  * Underlying type available via ::Type
  */
  template<typename T> struct RemoveCV { using Type = T; };
  template<typename T> struct RemoveCV<const T> { using Type = T; };
  template<typename T> struct RemoveCV<volatile T> { using Type = T; };
  template<typename T> struct RemoveCV<const volatile T> { using Type = T; };

  /*
  * Helper to access ::Type of RemoveCV
  */
  template<typename T> using RemoveCV_t = typename RemoveCV<T>::Type;

  /*
  * Helper to transfer cv-qualifiers from one type to another
  */
  template<typename T, typename U> 
  struct TransferCV
  {
    using InType = T;
    using OutType = U;
  };
  template<typename T, typename U>
  struct TransferCV<const T, U>
  {
    using InType = T;
    using OutType = const U;
  };
  template<typename T, typename U>
  struct TransferCV<volatile T, U>
  {
    using InType = T;
    using OutType = volatile U;
  };
  template<typename T, typename U>
  struct TransferCV<const volatile T, U>
  {
    using InType = T;
    using OutType = const volatile U;
  };

  /*
  * Helper to access ::Type of TransferCV
  */
  template<typename T, typename U> using TransferCV_t = typename TransferCV<T, U>::OutType;

}

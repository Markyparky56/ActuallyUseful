module;
export module autl.type_traits.constvolatile;

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
}

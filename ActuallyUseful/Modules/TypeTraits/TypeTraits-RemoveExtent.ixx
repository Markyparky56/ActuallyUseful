module;
export module autl.type_traits.removeextent;

import autl.types.std;

export namespace autl
{
  /*
  * If given type is an array, extract type as Type
  * Note: If T is a multi-dimensional array only the first dimension is remove
  *       Use RemoveAllExtents if wishing to remove all dimensions
  */
  template<typename T> struct RemoveExtent { using Type = T; };
  template<typename T> struct RemoveExtent<T[]> { using Type = T; };
  template<typename T, size_t N> struct RemoveExtent<T[N]> { using Type = T; };

  /*
  * Helper to access ::Type of RemoveExtent
  */
  template<typename T> using RemoveExtent_t = typename RemoveExtent<T>::Type;

  /*
  * If given type is an array, extract type as Type, removing all dimensions if present
  */
  template<typename T> struct RemoveAllExtents { using Type = T; };
  template<typename T> struct RemoveAllExtents<T[]> 
  {
    // Recurse until Type no longer matches as array
    using Type = typename RemoveAllExtents<T>::Type; 
  };
  template<typename T, size_t N> struct RemoveAllExtents<T[N]> 
  { 
    using Type = typename RemoveAllExtents<T>::Type; 
  };

  /*
  * Helper to access ::Type of RemoveAllExtents
  */
  template<typename T> using RemoveAllExtents_t = typename RemoveAllExtents<T>::Type;
}

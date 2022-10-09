module;
export module autl.type_traits.isspecialisation;

import autl.type_traits.integralconstant;

export namespace autl
{
  /*
  * True if (and only if) T is a specialisation of Template
  */
  template<class T, template<typename...> typename Template> 
  inline constexpr bool IsSpecialisation_v = false;
  template<template<typename...> typename Template, typename... Ts> 
  inline constexpr bool IsSpecialisation_v<Template<Ts...>, Template> = true;

  /*
  * [Non-standard]
  * Determine if T is a specialisation of Template
  */
  template<typename T, template<typename...> typename Template> 
  struct IsSpecialisation : BoolConstant<IsSpecialisation_v<T, Template>> {};
}
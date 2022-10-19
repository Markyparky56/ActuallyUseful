module;
export module autl.type_traits.isassignable;

import autl.type_traits.integralconstant;
import autl.type_traits.reference;

export namespace autl
{
  /*
  * True if From can be assigned to a To
  */
  template<typename To, typename From>
  struct IsAssignable 
    : BoolConstant<__is_assignable(To, From)> {};

  /*
  * Helper to access ::Value of IsAssignable
  */
  template<typename To, typename From> 
  inline constexpr bool IsAssignable_v = IsAssignable<To, From>::Value;

  /*
  * True if From can be assigned to To without calling any non-trivial operations
  */
  template<typename To, typename From>
  struct IsTriviallyAssignable 
    : BoolConstant<__is_trivially_assignable(To, From)> {};

  /*
  * Helper to access ::Value of IsTriviallyAssignable
  */
  template<typename To, typename From> 
  inline constexpr bool IsTriviallyAssignable_v = IsTriviallyAssignable<To, From>::Value;

  /*
  * True if From can be assigned to To without the chance of throwing an exception
  */
  template<typename To, typename From>
  struct IsNoThrowAssignable 
    : BoolConstant<__is_nothrow_assignable(To, From)> {};

  /*
  * Helper to access ::Value of IsNoThrowAssignable
  */
  template<typename To, typename From> 
  inline constexpr bool IsNoThrowAssignable_v = IsNoThrowAssignable<To, From>::Value;

  /*
  * True if a const To& can be assigned to a To&
  */
  template<typename To>
  struct IsCopyAssignable 
    : BoolConstant<__is_assignable(AddLValueReference_t<To>, AddLValueReference_t<const To>)> {};

  /*
  * Helper to access ::Value of IsCopyAssignable
  */
  template<typename To> 
  inline constexpr bool IsCopyAssignable_v = IsCopyAssignable<To>::Value;

  /*
  * True if a const To& can be assigned to a To& without calling any non-trivial operations
  */
  template<typename To>
  struct IsTriviallyCopyAssignable 
    : BoolConstant<__is_trivially_assignable(AddLValueReference_t<To>, AddLValueReference_t<const To>)> {};

  /*
  * Helper to access ::Value of IsTriviallyCopyAssignable
  */
  template<typename To> 
  inline constexpr bool IsTriviallyCopyAssignable_v = IsTriviallyCopyAssignable<To>::Value;

  /*
  * True if const From& can be assigned to To& without the chance of throwing an exception
  */
  template<typename To>
  struct IsNoThrowCopyAssignable 
    : BoolConstant<__is_nothrow_assignable(AddLValueReference_t<To>, AddLValueReference_t<const To>)> {};

  /*
  * Helper to access ::Value of IsNoThrowCopyAssignable
  */
  template<typename To> 
  inline constexpr bool IsNoThrowCopyAssignable_v = IsNoThrowCopyAssignable<To>::Value;

  //////

  /*
  * True if To&& can be move assigned to a To&
  */
  template<typename To>
  struct IsMoveAssignable 
    : BoolConstant<__is_assignable(AddLValueReference_t<To>, AddRValueReference_t<To>)> {};

  /*
  * Helper to access ::Value of IsMoveAssignable
  */
  template<typename To> inline constexpr bool IsMoveAssignable_v = IsMoveAssignable<To>::Value;

  /*
  * True if a To&& can be assigned to a To& without calling any non-trivial operations
  */
  template<typename To>
  struct IsTriviallyMoveAssignable
    : BoolConstant<__is_trivially_assignable(AddLValueReference_t<To>, AddRValueReference_t<To>)> {};

  /*
  * Helper to access ::Value of IsTriviallyMoveAssignable
  */
  template<typename To>
  inline constexpr bool IsTriviallyMoveAssignable_v = IsTriviallyMoveAssignable<To>::Value;

  /*
  * True if From&& can be assigned to To& without the chance of throwing an exception
  */
  template<typename To>
  struct IsNoThrowMoveAssignable
    : BoolConstant<__is_nothrow_assignable(AddLValueReference_t<To>, AddRValueReference_t<To>)> {};

  /*
  * Helper to access ::Value of IsNoThrowMoveAssignable
  */
  template<typename To>
  inline constexpr bool IsNoThrowMoveAssignable_v = IsNoThrowMoveAssignable<To>::Value;
}
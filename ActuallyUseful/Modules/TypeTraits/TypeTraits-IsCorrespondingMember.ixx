module;
export module autl.type_traits.iscorrespondingmember;

export namespace autl
{
  /*
  * Determine whether pmA and pmB refer to corresponding members in the "common initial sequence" of ClassA and Class B
  * The common initial sequence of two standard-layout non-union class types is the longest sequence of non-static data members and bit-fields in declaration order, starting with the first such entity in each of the classes
  * 
  * If either Class is not a standard layout class, 
  * or either Member is not an object type, 
  * or pmA or pmB is equal to nullptr, the result is always false
  */
  template<typename ClassA, typename ClassB, typename MemberA, typename MemberB>
  [[nodiscard]] constexpr bool IsCorrespondingMember(MemberA ClassA::* pmA, MemberB ClassB::* pmB) noexcept
  {
    // Only available in MSVC currently, work-in-progress for Clang, support seems to exist in GCC
    return __is_corresponding_member(ClassA, ClassB, pmA, pmB);
  }
}


#include "Invoke-UndefClassMacro.h"

#define CLASS_DEFINE_CV_REF_NOEXCEPT(Class) \
  Class() \
  Class(const) \
  Class(volatile) \
  Class(const volatile) \
  Class(&) \
  Class(const&) \
  Class(volatile&) \
  Class(const volatile&) \
  Class(&&) \
  Class(const&&) \
  Class(volatile&&) \
  Class(const volatile&&) \
  Class(noexcept) \
  Class(const noexcept) \
  Class(volatile noexcept) \
  Class(const volatile noexcept) \
  Class(&noexcept) \
  Class(const& noexcept) \
  Class(volatile& noexcept) \
  Class(const volatile& noexcept) \
  Class(&& noexcept) \
  Class(const&& noexcept) \
  Class(volatile&& noexcept) \
  Class(const volatile&& noexcept)


#include "Invoke-UndefMemberCallMacos.h"

#if !defined(_MSC_VER)
#define EMIT_CALL(Func, Opt1, Opt2, Opt3) Func(,Opt1, Opt2, Opt3)
#else
#define EMIT_CALL(Func, Opt1, Opt2, Opt3) \
  Func(__cdecl, Opt1, Opt2, Opt3)         \
  Func(__vectorcall, Opt1, Opt2, Opt3)
#endif // End !_MSC_VER

#define MEMBER_CALL_CV(Func, RefOpt, NoExceptOpt)     \
  EMIT_CALL(Func, , RefOpt, NoExceptOpt)              \
  EMIT_CALL(Func, const, RefOpt, NoExceptOpt)         \
  EMIT_CALL(Func, volatile, RefOpt, NoExceptOpt)      \
  EMIT_CALL(Func, const volatile, RefOpt, NoExceptOpt)

#define MEMBER_CALL_CV_REF(Func, NoExceptOpt) \
  MEMBER_CALL_CV(Func, , NoExceptOpt)         \
  MEMBER_CALL_CV(Func, &, NoExceptOpt)        \
  MEMBER_CALL_CV(Func, &&, NoExceptOpt)       \

#define MEMBER_CALL_CV_REF_NOEXCEPT(Func) \
  MEMBER_CALL_CV_REF(Func, )              \
  MEMBER_CALL_CV_REF(Func, noexcept)

module;
export module autl.types.std;

/*
* Standard common types
* 
*/
export namespace autl
{
  using nullptr_t = decltype(nullptr);

  // Use __int64 on MSVC?
  using size_t = unsigned long long;

  using ptrdiff_t = long long;

  using max_align_t = double;

  // ...

  using intptr_t = long long;
}

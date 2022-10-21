# The _ActuallyUseful_ Template Library

<sup><sub><sup>Did someone say feature creep?</sup></sub></sup>

The STL is great. _But..._ Us coders are fussy folks. I'm eternally bugged by its use of snake_case, everything being lowercase, and all the documentation being _not there_. _cppreference_ is a fantastic resource, but having to dip out to the web to work out what a function or structure is doing breaks my flow. 

I very much have Unreal C++ Stockholm Syndrome at this point. I enjoy being able to quickly dive into the engine's code files, nosey around and see what makes it tick. Most of the time the code is commented; functions say what they do, how, and why. And it's written in a sane coding style! _Mostly_. CamelCase, not snake_case. Allman-style function braces. No egregious use of underscores which blind you to the actual code. I'd love to see a STL that was written this way.

This is not that.

This is something else.

#### So what do we have here?

This is my attempt to pull together the useful, helpful components of the STL and Unreal's core functionality, re-written in modern C++20, and packaged up in C++ Standard Modules. (Why? Because.) Perhaps it'll be a foundation for future projects. Perhaps it'll just be a fun experiment.

And, like all good C++ projects, it's written in a coding style that is different to everything else out there. A healthy blend of CamelCase and lowerCamelCase. Allman-style braces. Underscores where only strictly necessary. It's beautiful, trust me. Don't worry, I'll only use Hungarian-notation for booleans, I swear.

For the moment, this project is solely compatible with Windows and MSVC. I would have loved to build this with Premake or CMake, but Clang and GCC still have little to no support for module dependencies (and CMake support for C++ Modules is still experimental as a result). I'd rather not spend my spare time hand-writing all the compiler permutations for this library. Clang and GCC will catch up in time, and until then, MSVC gets to be weird with its `.ixx` files.

#### Do you have a plan?

_Kinda sorta maybe_

This library will grow organically. My time is limited and I have other hobbies. For now, my aim is to implement (in no particular order)

- Various `algo` sub-modules, pulling from those found in `<algorithm>` and any interesting extensions/additions that Unreal Engine might have that look useful.
- Invoke, out of necessity for the above algorithms
- A raft of useful `utility` sub-modules like `BitCast` and `AlignedBytes`
- A mostly (or fully) realised `type_traits` sub-module, which is proving to be the cornerstone for the rest of the library. Whodathunk templates need so many helpers?
- A `types` sub-module and accompany `limits` sub-module for standard type names and numeric limits for them
- Concepts
- Containers, including:
  - A dynamic array akin to `TArray`
    - Accompanying ArrayView (or do we call it Span now?)
  - List (or LinkedList?), DoubleLinkedList
  - Map & Set
  - Circular Buffer/Ring Buffer
- A handy-dandy String implementation
- Smart Pointers
  - UniquePtr and SharedPtr, WeakPtr
  - Maybe pull in SharedRef (and UniqueObj) since they're really neat
- Allocators compatible with the containers listed above
  - Sized
  - Aligned/SizedAligned
  - Inline
    - Honestly, `TInlineAllocator` haunts my dreams it's so nice
  - Fixed
- Asserts
  - check/checkMsgf
  - ensure/ensureMsgf
  - verify/verifyMsgf
  - Maybe some kind of stack dump if we're feeling brave
- Random
  - Your typical Mersenne Twister
  - xoshiro / xoroshiro generators from https://prng.di.unimi.it/
  - Rand Range Helpers + Cone Helpers
- Explore replacement memory functions like `memcpy` and how one might conditionally integrate replacement low-level allocators such as `mimalloc` or `dlmalloc`

Some stretch goals that may end up being moved to a secondary "ToolBox" library which builds off this one:

- Delegates, integrating with smart pointers
- A centralised Message Broadcast system for when delegates create too much inflexible coupling
- A Push-Model Message system for when delegates go the wrong way and broadcast messages are wasteful

Safe to say, this code is reminiscent of other STLs, but makes no attempt to be fully conformant or include every niche feature on offer. As the name suggests, it seeks to be useful, and if it succeeds in providing the tools I need to do other fun things, it'll have been worth it. As long as IntelliSense holds up.

#### But, how?

What we have now is largely based on implementations found in the MSVC STL and libcxx (the one from llvm). Both of these are _very_ different. This is very much fusion cooking. A sprinkle of MSVC, a dash of libcxx, _cppreference_ by the bucket full, garnished with Unreal's special sauce.

Perhaps I'm hungry.

Simply put, I definitely don't have the know-how to write this purely from spec docs and reference material. So, I'm doing this like I learnt to program and copying someone better than me, re-writing as I go, reformatting to fit my preferred style and tweaking and updating where I can. 

C++ Modules are a firebreak in the C++ versioning and offer a chance to strip out a lot of the old backwards compatibility baked into existing STL code. They come part-in-parcel with C++20 and all the fun toys that entails. This largely means Concepts and Constraints. `requires` is a breath of fresh air next to the arcane, esoteric hijinks of `enable_if`. `void_t` doesn't look like it's shifting sadly and that thing's almost as bad, or maybe worse? Either way, this is a chance to exercise those template meta-programming muscles I've been neglecting.

#### What about licenses and copyright? Is any of this legal?

**I AM NOT A LAWYER BY ANY MEANS**

The biggest question here is what qualifies as a "Derivative Work".

Both MSVC and libcxx are released under the `Apache-2.0 WITH LLVM-exception` license [(link)](https://spdx.org/licenses/LLVM-exception.html). I contemplated comparing implementations with GCC _but_ the `GPL` is a scary scary beast.

Unreal has its own License/EULA that is surprisingly permissive when it comes to studying its source code. [License/EULA](https://www.unrealengine.com/en-US/eula/unreal), [FAQ](https://www.unrealengine.com/en-US/faq?active=source)

> Code is copyrighted, but knowledge is free!

As a matter of principle, I don't copy-paste code. It's not useful to facilitate learning and is blatant copying. I'd like to hope whatever I'm doing produces a result different enough to convey this is something uniquely mine. Neither MSVC, libcxx, nor Unreal have formatted their source as C++ Modules, nor rewritten their code to use C++20 features. Still, there is no denying this code has its roots in theirs.

However the chips fall, whether it'll be Tim Sweeny beating down my door, or someone from Microsoft, or the LLVM Foundation, I'm not doing this with the intent to misrepresent the origin or inspiration for this project and its source code. Indeed, using Unreal Engine for so long drove me to attempt this project.

I just want a template library that doesn't make me contort my hand from all the underscores.

Yes, really.

No, you type weird.

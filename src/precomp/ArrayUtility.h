#pragma once

#include <stddef.h>

// Element count of a statically sized array, as an `int`.
//
// Same deduction trick as the CRT's `_countof` (MSVC1400-SP1, stdlib.h): the helper is declared but
// never defined, its return type is a pointer to `char[N]`, and `sizeof` on the dereferenced result
// yields `N` as a compile-time constant. Unlike `_countof` the result is cast to `int`, so
// `i < countof(array)` keeps the signed comparison (`jl`) the original game code emits instead of
// promoting the loop variable to unsigned (`jb`).
//
// Passing a pointer rather than an array is a compile error, which the `sizeof(a) / sizeof(a[0])`
// macro form would silently accept.
extern "C++" {
template <typename CountofType, size_t SizeOfArray>
char (*__countof_int_helper(CountofType (&Array)[SizeOfArray]))[SizeOfArray];
}
#define countof(Array) ((int)sizeof(*__countof_int_helper(Array)))

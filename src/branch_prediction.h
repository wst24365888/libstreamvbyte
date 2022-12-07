#pragma once

// [[likely]] and [[unlikely]] are introduced in C++20
// since cibuildwheel supports up to C++17, we need to define them ourselves
// https://en.cppreference.com/w/cpp/language/attributes/likely
// https://cibuildwheel.readthedocs.io/en/stable/cpp_standards/

#ifndef LIKELY
#if defined(__GNUC__) || defined(__clang__)
#define LIKELY(x) __builtin_expect(!!(x), 1)
#else
#define LIKELY(x) (x)
#endif
#endif

#ifndef UNLIKELY
#if defined(__GNUC__) || defined(__clang__)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define UNLIKELY(x) (x)
#endif
#endif
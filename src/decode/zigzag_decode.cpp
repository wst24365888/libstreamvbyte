#include "zigzag_decode_scalar.hpp"
#include "streamvbyte.h"
#include <vector>

#if defined(_MSC_VER) && defined(_M_AMD64)
#include "zigzag_decode_vectorized.hpp"
#elif defined(__SSSE3__) || defined(__NEON__)
#include "zigzag_decode_vectorized.hpp"
#endif

void streamvbyte::zigzag_decode(const uint32_t* in, std::size_t count, int32_t* out) {
    if (UNLIKELY(count == 0)) {
        return;
    }

#if defined(_MSC_VER) && defined(_M_AMD64)
    zigzag_decode_vectorized(in, count, out); // side effect: count, out are modified
#elif defined(__SSSE3__) || defined(__NEON__)
    zigzag_decode_vectorized(in, count, out); // side effect: count, out are modified
#endif

    zigzag_decode_scalar(in, count, out); // side effect: count, out are modified
}

std::vector<int32_t> streamvbyte::zigzag_decode(const std::vector<uint32_t>& in) {
    std::vector<int32_t> out(in.size());
    zigzag_decode(in.data(), in.size(), out.data());
    return out;
}
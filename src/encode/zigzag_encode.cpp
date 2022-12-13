#include "zigzag_encode_scalar.hpp"
#include "streamvbyte.h"
#include <vector>

#if defined(_MSC_VER) && defined(_M_AMD64)
#include "zigzag_encode_vectorized.hpp"
#elif defined(__SSSE3__) || defined(__NEON__)
#include "zigzag_encode_vectorized.hpp"
#endif

void streamvbyte::zigzag_encode(const int32_t* in, std::size_t count, uint32_t* out) {

#if defined(_MSC_VER) && defined(_M_AMD64)
    zigzag_encode_vectorized(in, count, out); // side effect: count, out are modified
#elif defined(__SSSE3__) || defined(__NEON__)
    zigzag_encode_vectorized(in, count, out); // side effect: count, out are modified
#endif

    zigzag_encode_scalar(in, count, out); // side effect: count, out are modified
}

std::vector<uint32_t> streamvbyte::zigzag_encode(const std::vector<int32_t>& in) {
    std::vector<uint32_t> out(in.size());
    zigzag_encode(in.data(), in.size(), out.data());
    return out;
}
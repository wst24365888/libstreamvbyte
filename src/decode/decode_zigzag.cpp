#include "decode_zigzag_scalar.hpp"
#include "streamvbyte.h"
#include <vector>

#if defined(_MSC_VER) && defined(_M_AMD64)
#include "decode_zigzag_ssse3.hpp"
#endif

#if defined(__SSSE3__)
#include "decode_zigzag_ssse3.hpp"
#endif

void streamvbyte::decode_zigzag(const uint32_t* in, std::size_t count, int32_t* out) {

#if defined(_MSC_VER) && defined(_M_AMD64)
    decode_zigzag_ssse3(in, count, out);    // side effect: count, out are modified
#endif

#if defined(__SSSE3__)
    decode_zigzag_ssse3(in, count, out);    // side effect: count, out are modified
#endif

    decode_zigzag_scalar(in, count, out);    // side effect: count, out are modified
}

std::vector<int32_t> streamvbyte::decode_zigzag(const std::vector<uint32_t>& in) {
    std::vector<int32_t> out(in.size());
    decode_zigzag(in.data(), in.size(), out.data());
    return out;
}
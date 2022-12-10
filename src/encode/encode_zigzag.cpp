#include "encode_zigzag_scalar.hpp"
#include "streamvbyte.h"
#include <vector>

#if defined(_MSC_VER) && defined(_M_AMD64)
#include "encode_zigzag_ssse3.hpp"
#endif

#if defined(__SSSE3__)
#include "encode_zigzag_ssse3.hpp"
#endif

void streamvbyte::encode_zigzag(const int32_t* in, std::size_t count, uint32_t* out) {

#if defined(_MSC_VER) && defined(_M_AMD64)
    encode_zigzag_ssse3(in, count, out);    // side effect: count, out are modified
#endif

#if defined(__SSSE3__)
    encode_zigzag_ssse3(in, count, out);    // side effect: count, out are modified
#endif

    encode_zigzag_scalar(in, count, out);    // side effect: count, out are modified
}

std::vector<uint32_t> streamvbyte::encode_zigzag(const std::vector<int32_t>& in) {
    std::vector<uint32_t> out(in.size());
    encode_zigzag(in.data(), in.size(), out.data());
    return out;
}
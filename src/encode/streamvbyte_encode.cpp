#include "streamvbyte_encode_scalar.hpp"
#include "streamvbyte.h"
#include <vector>

#if defined(_MSC_VER) && defined(_M_AMD64)
#include "streamvbyte_encode_vectorized.hpp"
#elif defined(__SSSE3__) || defined(__NEON__)
#include "streamvbyte_encode_vectorized.hpp"
#endif

std::size_t streamvbyte::encode(const uint32_t* in, std::size_t count, uint8_t* out) {
    uint8_t* control_stream = out;
    uint8_t* data_stream = out + (count + 3) / 4;

#if defined(_MSC_VER) && defined(_M_AMD64)
    encode_vectorized(in, count, control_stream, data_stream); // side effect: all arguments are modified
#elif defined(__SSSE3__) || defined(__NEON__)
    encode_vectorized(in, count, control_stream, data_stream); // side effect: all arguments are modified
#endif

    encode_scalar(in, count, control_stream, data_stream); // side effect: count, control_stream, data_stream are modified

    return data_stream - out;
}

std::vector<uint8_t> streamvbyte::encode(const std::vector<uint32_t>& in) {
    std::vector<uint8_t> out(max_compressed_size(in.size()));
    std::size_t size = encode(in.data(), in.size(), out.data());
    out.resize(size);
    return out;
}
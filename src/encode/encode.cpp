#include "encode_scalar.hpp"
#include "streamvbyte.h"
#include <vector>

#if defined(__SSSE3__)
#include "encode_ssse3.hpp"
#endif

std::size_t streamvbyte::encode(const uint32_t* in, std::size_t count, uint8_t* out) {
    uint8_t* control_stream = out;
    uint8_t* data_stream = out + (count + 3) / 4;

#if defined(__SSSE3__)
    encode_ssse3(in, count, control_stream, data_stream); // side effect: all arguments are modified
#endif

    encode_scalar(in, count, control_stream, data_stream); // side effect: count, control_stream, data_stream are modified

    return data_stream - out;
}

std::vector<uint8_t> streamvbyte::encode(const std::vector<uint32_t>& in) {
    std::vector<uint8_t> out((in.size() + 3) / 4 + in.size() * sizeof(uint32_t));
    std::size_t size = encode(in.data(), in.size(), out.data());
    out.resize(size);
    return out;
}
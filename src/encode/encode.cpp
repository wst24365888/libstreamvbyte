#include "encode_scalar.hpp"
#include "streamvbyte.h"

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
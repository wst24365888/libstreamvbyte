#include "encode_scalar.hpp"
#include "streamvbyte.h"

#if defined(__SSSE3__)
#include "encode_ssse3.hpp"
#endif

std::size_t stringvbyte::encode(const uint32_t* in, std::size_t count, uint8_t* out) {
    uint8_t* control_stream = out;
    uint8_t* data_stream = out + (count + 3) / 4;

#if defined(__SSSE3__)
    stringvbyte::encode_ssse3(in, count, control_stream, data_stream); // side effect: count, control_stream and data_stream are updated
#endif

    encode_scalar(in, count, control_stream, data_stream); // side effect: control_stream and data_stream are updated

    return control_stream - out;
}
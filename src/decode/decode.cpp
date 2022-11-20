#include "decode_scalar.hpp"
#include "streamvbyte.h"
#include <iostream>

#if defined(__SSSE3__)
#include "decode_ssse3.hpp"
#endif

std::size_t streamvbyte::decode(const uint8_t* in, uint32_t* out, std::size_t count) {
    const uint8_t* control_stream = in;
    const uint8_t* data_stream = in + (count + 3) / 4;

#if defined(__SSSE3__)
    data_stream = decode_ssse3(out, count, control_stream, data_stream);
#endif

    data_stream = decode_scalar(out, count, control_stream, data_stream);

    return data_stream - in;
}
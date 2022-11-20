#include "decode_scalar.hpp"
#include "streamvbyte.h"
#include <iostream>

std::size_t streamvbyte::decode(const uint8_t* in, uint32_t* out, std::size_t count) {
    const uint8_t* control_stream = in;
    const uint8_t* data_stream = in + (count + 3) / 4;

    data_stream = decode_scalar(out, count, control_stream, data_stream);

    return data_stream - in;
}
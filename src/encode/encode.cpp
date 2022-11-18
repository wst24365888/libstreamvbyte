#include "encode_scalar.hpp"
#include "streamvbyte.h"

std::size_t stringvbyte::encode(const uint32_t* in, std::size_t count, uint8_t* out) {
    uint8_t* control_stream = out;
    uint8_t* data_stream = out + (count + 3) / 4;

#ifdef __AVX2__
    if (count >= 16) {
        uint8_t* control_stream_end = encode_avx2(in, control_stream, data_stream, count);
        return control_stream_end - out;
    }
#endif

    control_stream = encode_scalar(in, control_stream, data_stream, count);

    return control_stream - out;
}
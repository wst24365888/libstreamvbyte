#ifndef ENCODE_SCALAR
#define ENCODE_SCALAR

#include "branch_prediction.h"
#include <iostream>

static uint8_t encode_data(uint32_t value, uint8_t** data_stream_ptr) {
    uint8_t control_bits = (value >= (1U << 8)) + (value >= (1U << 16)) + (value >= (1U << 24));
    *(reinterpret_cast<uint32_t*>(*data_stream_ptr)) = value;
    *data_stream_ptr += 1 + control_bits;
    return control_bits;
}

static uint8_t* encode_scalar(const uint32_t* in, const std::size_t count, uint8_t* control_stream, uint8_t* data_stream) {
    uint8_t shift = 0;
    uint8_t control_bits = 0;
    for (std::size_t i = 0; LIKELY(i < count); i++) {
        control_bits |= encode_data(in[i], &data_stream) << shift;
        shift += 2;

        if (UNLIKELY(shift == 8)) {
            *control_stream = control_bits;
            control_stream++;
            shift = 0;
            control_bits = 0;
        }
    }

    if (LIKELY(shift != 0)) {
        *control_stream = control_bits;
        control_stream++;
    }
    return data_stream;
}

#endif

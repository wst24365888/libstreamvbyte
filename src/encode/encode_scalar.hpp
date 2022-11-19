#pragma once

#include <iostream>
#include <branch_prediction.h>

static uint8_t encode_data(uint32_t value, uint8_t** data_stream_ptr) {
    if (value < (1U << 8)) {
        **data_stream_ptr = static_cast<uint8_t>(value);
        (*data_stream_ptr)++;

        return 0b00;
    } else if (value < (1U << 16)) {
        **data_stream_ptr = static_cast<uint8_t>(value);
        (*data_stream_ptr)++;
        **data_stream_ptr = static_cast<uint8_t>(value >> 8);
        (*data_stream_ptr)++;

        return 0b01;
    } else if (value < (1U << 24)) {
        **data_stream_ptr = static_cast<uint8_t>(value);
        (*data_stream_ptr)++;
        **data_stream_ptr = static_cast<uint8_t>(value >> 8);
        (*data_stream_ptr)++;
        **data_stream_ptr = static_cast<uint8_t>(value >> 16);
        (*data_stream_ptr)++;

        return 0b10;
    } else {
        **data_stream_ptr = static_cast<uint8_t>(value);
        (*data_stream_ptr)++;
        **data_stream_ptr = static_cast<uint8_t>(value >> 8);
        (*data_stream_ptr)++;
        **data_stream_ptr = static_cast<uint8_t>(value >> 16);
        (*data_stream_ptr)++;
        **data_stream_ptr = static_cast<uint8_t>(value >> 24);
        (*data_stream_ptr)++;

        return 0b11;
    }
}

static void encode_scalar(const uint32_t* in, const std::size_t count, uint8_t* control_stream, uint8_t* data_stream) {
    if (UNLIKELY(count == 0)) {
        return;
    }

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
}
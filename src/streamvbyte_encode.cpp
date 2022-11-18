#include "streamvbyte.h"

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

static uint8_t* encode_scalar(const uint32_t* in, uint8_t* control_stream, uint8_t* data_stream, std::size_t count) {
    if (count == 0) {
        return control_stream;
    }

    uint8_t shift = 0;
    uint8_t control_bits = 0;
    for (std::size_t i = 0; i < count; i++) {
        control_bits |= encode_data(in[i], &data_stream) << shift;
        shift += 2;

        if (shift == 8) {
            *control_stream = control_bits;
            control_stream++;
            shift = 0;
            control_bits = 0;
        }
    }
    
    if (shift != 0) {
        *control_stream = control_bits;
        control_stream++;
    }

    return control_stream;
}

std::size_t stringvbyte::encode(const uint32_t* in, std::size_t count, uint8_t* out) {
    uint8_t* control_stream = out;
    uint8_t* data_stream = out + (count + 3) / 4;

    control_stream = encode_scalar(in, control_stream, data_stream, count);

    return control_stream - out;
}
#include "decode_zigzag_scalar.hpp"
#include "streamvbyte.h"
#include <vector>

void streamvbyte::decode_zigzag(const uint32_t* in, std::size_t count, int32_t* out) {
    decode_zigzag_scalar(in, count, out);    // side effect: count, out are modified
}
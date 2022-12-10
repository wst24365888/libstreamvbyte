#include "encode_zigzag_scalar.hpp"
#include "streamvbyte.h"
#include <vector>

void streamvbyte::encode_zigzag(const int32_t* in, std::size_t count, uint32_t* out) {
    encode_zigzag_scalar(in, count, out);
}
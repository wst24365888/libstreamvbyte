#ifndef DECODE_ZIGZAG_SCALAR
#define DECODE_ZIGZAG_SCALAR

#include "branch_prediction.h"
#include <iostream>
#include <chrono>

static void decode_zigzag_scalar(const uint32_t*& in, std::size_t& count, int32_t*& out) {
    auto start = std::chrono::high_resolution_clock::now();
    std::size_t original_count = count;

    for (std::size_t i = 0; LIKELY(i < original_count); ++i) {
        uint32_t value = *in;
        int32_t zigzag = (value >> 1) ^ -(value & 1);
        *out = zigzag;

        ++in;
        ++out;
        --count;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "decode_zigzag_scalar: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns, processed " << original_count - count << " elements" << std::endl;
}

#endif
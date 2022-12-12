#ifndef zigzag_decode_SCALAR
#define zigzag_decode_SCALAR

#include "branch_prediction.h"
#include <config.h>
#include <iostream>

#ifdef PRINT_BENCHMARK
#include <chrono>
#endif

static void zigzag_decode_scalar(const uint32_t*& in, std::size_t& count, int32_t*& out) {
#ifdef PRINT_BENCHMARK
    auto start = std::chrono::high_resolution_clock::now();
#endif

    std::size_t original_count = count;

    for (std::size_t i = 0; LIKELY(i < original_count); ++i) {
        uint32_t value = *in;
        int32_t zigzag = (value >> 1) ^ -(value & 1);
        *out = zigzag;

        ++in;
        ++out;
        --count;
    }

#ifdef PRINT_BENCHMARK
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "zigzag_decode_scalar: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns, processed " << original_count - count << " elements" << std::endl;
#endif
}

#endif
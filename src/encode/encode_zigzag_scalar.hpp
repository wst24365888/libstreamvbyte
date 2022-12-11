#ifndef ENCODE_ZIGZAG_SCALAR
#define ENCODE_ZIGZAG_SCALAR

#include "branch_prediction.h"
#include <iostream>
#include <config.h>

#ifdef PRINT_BENCHMARK
#include <chrono>
#endif

static void encode_zigzag_scalar(const int32_t*& in, std::size_t& count, uint32_t*& out) {
    #ifdef PRINT_BENCHMARK
    auto start = std::chrono::high_resolution_clock::now();
    #endif

    std::size_t original_count = count;

    for (std::size_t i = 0; LIKELY(i < original_count); ++i) {
        int32_t value = *in;
        uint32_t zigzag = (value >> 31) ^ (value << 1);
        *out = zigzag;

        ++in;
        ++out;
        --count;
    }

    #ifdef PRINT_BENCHMARK
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "encode_zigzag_scalar: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns, processed " << original_count - count << " elements" << std::endl;
    #endif
}

#endif
#ifndef DECODE_ZIGZAG_SSSE3
#define DECODE_ZIGZAG_SSSE3

#include "branch_prediction.h"
#include "tmmintrin.h"
#include <iostream>
#include <chrono>

static void decode_zigzag_ssse3(const uint32_t*& in, std::size_t& count, int32_t*& out) {
    auto start = std::chrono::high_resolution_clock::now();
    std::size_t original_count = count;

    for (std::size_t i = 0; LIKELY(i < original_count / 4); i++) {
        __m128i input = _mm_loadu_si128(reinterpret_cast<const __m128i*>(in));
        __m128i output = _mm_srli_epi32(input, 1);
        __m128i sign = _mm_and_si128(input, _mm_set1_epi32(1));
        sign = _mm_sub_epi32(_mm_set1_epi32(0), sign);
        output = _mm_xor_si128(output, sign);
        _mm_storeu_si128(reinterpret_cast<__m128i*>(out), output);

        in += 4;
        out += 4;
        count -= 4;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "decode_zigzag_ssse3: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns, processed " << original_count - count << " elements" << std::endl;
}

#endif
#ifndef ENCODE_ZIGZAG_SSSE3
#define ENCODE_ZIGZAG_SSSE3

#include "branch_prediction.h"
#include "tmmintrin.h"
#include <iostream>
#include <chrono>

static void encode_zigzag_ssse3(const int32_t*& in, std::size_t& count, uint32_t*& out) {
    auto start = std::chrono::high_resolution_clock::now();
    std::size_t original_count = count;

    for (std::size_t i = 0; LIKELY(i < original_count / 4); i++) {
        __m128i input = _mm_loadu_si128(reinterpret_cast<const __m128i*>(in));
        __m128i sign = _mm_srai_epi32(input, 31);
        __m128i output = _mm_slli_epi32(input, 1);
        output = _mm_xor_si128(output, sign);
        _mm_storeu_si128(reinterpret_cast<__m128i*>(out), output);

        in += 4;
        out += 4;
        count -= 4;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "encode_zigzag_ssse3: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns, processed " << original_count - count << " elements" << std::endl;
}

#endif
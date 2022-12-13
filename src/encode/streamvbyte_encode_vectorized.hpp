#ifndef ENCODE_SSSE3
#define ENCODE_SSSE3

#include "branch_prediction.h"
#include "encode_shuffle_table.h"
#include "length_table.h"
#include <config.h>
#include <iostream>
#include <tuple>

#ifdef __NEON__
#include "sse2neon.h"
#else
#include <tmmintrin.h>
#endif

#ifdef PRINT_BENCHMARK
#include <chrono>
#endif

static void encode_vectorized(const uint32_t*& in, std::size_t& count, uint8_t*& control_stream, uint8_t*& data_stream) {
#ifdef PRINT_BENCHMARK
    auto start = std::chrono::high_resolution_clock::now();
#endif

    std::size_t original_count = count;

    const __m128i mask_test_byte = _mm_set1_epi8(0x11);
    const __m128i mask_clear_low_bits = _mm_set1_epi16(0x0100);
    const __m128i mask_mscb = _mm_set1_epi16(0x7f00); // most significant control bit

    for (std::size_t i = 0; LIKELY(i < original_count / 8); ++i) {
        __m128i r0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(in + 0));
        __m128i r1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(in + 4));

        __m128i r2 = _mm_min_epu8(r0, mask_test_byte);
        __m128i r3 = _mm_min_epu8(r1, mask_test_byte);

        r2 = _mm_packus_epi16(r2, r3);
        r2 = _mm_min_epi16(r2, mask_clear_low_bits);
        r2 = _mm_adds_epu16(r2, mask_mscb); // 7F00 -> 00 (only when uint32_t value is 0), 7F01 -> 00, 7FFF -> 01, 8000 -> 10, FFFF -> 11

        std::size_t control_bits = _mm_movemask_epi8(r2);

        r2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&encode_shffule_table[(control_bits << 4) & 0x03F0]));
        r3 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(&encode_shffule_table[(control_bits >> 4) & 0x03F0]));
        r0 = _mm_shuffle_epi8(r0, r2);
        r1 = _mm_shuffle_epi8(r1, r3);

        _mm_storeu_si128(reinterpret_cast<__m128i*>(data_stream), r0);
        data_stream += length_table[control_bits & 0xFF];
        _mm_storeu_si128(reinterpret_cast<__m128i*>(data_stream), r1);
        data_stream += length_table[control_bits >> 8];

        *(reinterpret_cast<uint16_t*>(control_stream)) = static_cast<uint16_t>(control_bits);
        control_stream += 2;

        in += 8;
        count -= 8;
    }

#ifdef PRINT_BENCHMARK
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "encode_vectorized: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns, processed " << original_count - count << " elements" << std::endl;
#endif
}

#endif

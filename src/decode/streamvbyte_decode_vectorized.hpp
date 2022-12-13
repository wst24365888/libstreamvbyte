#ifndef DECODE_SSSE3
#define DECODE_SSSE3

#include "branch_prediction.h"
#include "decode_shuffle_table.h"
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

static inline __m128i decode_data(uint32_t control_bits, const uint8_t** data_stream_ptr) {
    __m128i data = _mm_loadu_si128(reinterpret_cast<const __m128i*>(*data_stream_ptr));
    __m128i shuffle_mask = _mm_loadu_si128(reinterpret_cast<const __m128i*>(decode_shffule_table + (control_bits << 4)));

    data = _mm_shuffle_epi8(data, shuffle_mask);

    *data_stream_ptr += length_table[control_bits];

    return data;
}

static void decode_vectorized(uint32_t*& out, std::size_t& count, const uint8_t*& control_stream, const uint8_t*& data_stream) {
#ifdef PRINT_BENCHMARK
    auto start = std::chrono::high_resolution_clock::now();
#endif

    std::size_t original_count = count;

    for (std::size_t i = 0; LIKELY(i < original_count / 8); ++i) {
        uint32_t control_bits = *(reinterpret_cast<const uint16_t*>(control_stream));
        control_stream += 2;

        __m128i r0 = decode_data(control_bits & 0xFF, &data_stream);
        __m128i r1 = decode_data(control_bits >> 8, &data_stream);

        _mm_storeu_si128(reinterpret_cast<__m128i*>(out + 0), r0);
        _mm_storeu_si128(reinterpret_cast<__m128i*>(out + 4), r1);

        out += 8;
        count -= 8;
    }

#ifdef PRINT_BENCHMARK
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "decode_vectorized: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns, processed " << original_count - count << " elements" << std::endl;
#endif
}

#endif

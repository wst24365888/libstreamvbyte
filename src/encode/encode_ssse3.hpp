#pragma once

#include "branch_prediction.h"
#include "tmmintrin.h"
#include <iostream>

static void encode_ssse3(const uint32_t* in, std::size_t& count, uint8_t*& control_stream, uint8_t*& data_stream) {
    for (std::size_t i = 0; LIKELY(i < count / 8); i++) {
        __m128i r0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(in + i * 8 + 0));
        __m128i r1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(in + i * 8 + 4));

        __m128i r2 = _mm_and_si128(r0, _mm_set1_epi8(0x11));
        __m128i r3 = _mm_and_si128(r1, _mm_set1_epi8(0x11));

        r2 = _mm_packus_epi16(r2, r3);
        r2 = _mm_min_epi16(r2, _mm_set1_epi16(0x0100));
        r2 = _mm_adds_epu16(r2, _mm_set1_epi16(0x7f00));

        std::size_t control_bits = _mm_movemask_epi8(r2);
    }
}
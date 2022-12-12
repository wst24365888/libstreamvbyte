#include <benchmark/benchmark.h>
#include "streamvbyte.h"

static void BM_streamvbyte_encode(benchmark::State& state) {
    std::size_t N = state.range(0);

    uint32_t* original_data = new uint32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand();
    }

    uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];

    for (auto _ : state) {
        streamvbyte::encode(original_data, N, compressed_bytes);
    }

    delete[] original_data;
    delete[] compressed_bytes;
}

static void BM_streamvbyte_decode(benchmark::State& state) {
    std::size_t N = state.range(0);

    uint32_t* original_data = new uint32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand();
    }

    uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];
    streamvbyte::encode(original_data, N, compressed_bytes);

    uint32_t* recovered_data = new uint32_t[N];

    for (auto _ : state) {
        streamvbyte::decode(compressed_bytes, recovered_data, N);
    }

    delete[] original_data;
    delete[] compressed_bytes;
    delete[] recovered_data;
}

static void BM_streamvbyte_encode_zigzag(benchmark::State& state) {
    std::size_t N = state.range(0);

    int32_t* original_data = new int32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() - rand();
    }

    uint32_t* encoded_unsigend_integers = new uint32_t[N];

    for (auto _ : state) {
        streamvbyte::encode_zigzag(original_data, N, encoded_unsigend_integers);
    }

    delete[] original_data;
    delete[] encoded_unsigend_integers;
}

static void BM_streamvbyte_decode_zigzag(benchmark::State& state) {
    std::size_t N = state.range(0);

    int32_t* original_data = new int32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() - rand();
    }

    uint32_t* encoded_unsigend_integers = new uint32_t[N];
    streamvbyte::encode_zigzag(original_data, N, encoded_unsigend_integers);

    int32_t* recovered_data = new int32_t[N];

    for (auto _ : state) {
        streamvbyte::decode_zigzag(encoded_unsigend_integers, N, recovered_data);
    }

    delete[] original_data;
    delete[] encoded_unsigend_integers;
    delete[] recovered_data;
}

BENCHMARK(BM_streamvbyte_encode)->Range(1 << 20, 1 << 20);
BENCHMARK(BM_streamvbyte_encode)->Range(1 << 30, 1 << 30)->Iterations(100);
BENCHMARK(BM_streamvbyte_decode)->Range(1 << 20, 1 << 20);
BENCHMARK(BM_streamvbyte_decode)->Range(1 << 30, 1 << 30)->Iterations(100);
BENCHMARK(BM_streamvbyte_encode_zigzag)->Range(1 << 20, 1 << 20);
BENCHMARK(BM_streamvbyte_encode_zigzag)->Range(1 << 30, 1 << 30)->Iterations(100);
BENCHMARK(BM_streamvbyte_decode_zigzag)->Range(1 << 20, 1 << 20);
BENCHMARK(BM_streamvbyte_decode_zigzag)->Range(1 << 30, 1 << 30)->Iterations(100);

BENCHMARK_MAIN();
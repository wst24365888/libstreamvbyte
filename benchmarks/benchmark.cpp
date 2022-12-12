#include "streamvbyte.h"
#include <benchmark/benchmark.h>

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

    state.counters["Throughput"] = benchmark::Counter(int64_t(state.iterations()) * int64_t(N) * int64_t(sizeof(uint32_t)), benchmark::Counter::kIsRate);

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

    state.counters["Throughput"] = benchmark::Counter(int64_t(state.iterations()) * int64_t(N) * int64_t(sizeof(uint32_t)), benchmark::Counter::kIsRate);

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

    state.counters["Throughput"] = benchmark::Counter(int64_t(state.iterations()) * int64_t(N) * int64_t(sizeof(uint32_t)), benchmark::Counter::kIsRate);

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

    state.counters["Throughput"] = benchmark::Counter(int64_t(state.iterations()) * int64_t(N) * int64_t(sizeof(uint32_t)), benchmark::Counter::kIsRate);

    delete[] original_data;
    delete[] encoded_unsigend_integers;
    delete[] recovered_data;
}

BENCHMARK(BM_streamvbyte_encode)->RangeMultiplier(10)->Range(1e6, 1e9)->MinTime(10);
BENCHMARK(BM_streamvbyte_decode)->RangeMultiplier(10)->Range(1e6, 1e9)->MinTime(10);
BENCHMARK(BM_streamvbyte_encode_zigzag)->RangeMultiplier(10)->Range(1e6, 1e9)->MinTime(10);
BENCHMARK(BM_streamvbyte_decode_zigzag)->RangeMultiplier(10)->Range(1e6, 1e9)->MinTime(10);

BENCHMARK_MAIN();
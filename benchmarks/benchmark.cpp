#include "streamvbyte.h"
#include <benchmark/benchmark.h>
#include <cstring>

static void BM_memcpy(benchmark::State& state) {
    std::size_t N = state.range(0);

    uint32_t* src = new uint32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        src[i] = rand() >> (rand() & 0b11111);
    }

    uint32_t* dst = new uint32_t[N];

    for (auto _ : state) {
        memcpy(dst, src, N * sizeof(uint32_t));
    }

    state.counters["Throughput"] = benchmark::Counter(state.iterations() * N * sizeof(uint32_t) / 8, benchmark::Counter::kIsRate);

    delete[] src;
    delete[] dst;
}

static void BM_streamvbyte_encode(benchmark::State& state) {
    std::size_t N = state.range(0);

    uint32_t* original_data = new uint32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() >> (rand() & 0b11111);
    }

    uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];

    for (auto _ : state) {
        streamvbyte::encode(original_data, N, compressed_bytes);
    }

    state.counters["Throughput"] = benchmark::Counter(state.iterations() * N * sizeof(uint32_t) / 8, benchmark::Counter::kIsRate);

    delete[] original_data;
    delete[] compressed_bytes;
}

static void BM_streamvbyte_decode(benchmark::State& state) {
    std::size_t N = state.range(0);

    uint32_t* original_data = new uint32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() >> (rand() & 0b11111);
    }

    uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];
    streamvbyte::encode(original_data, N, compressed_bytes);

    uint32_t* recovered_data = new uint32_t[N];

    for (auto _ : state) {
        streamvbyte::decode(compressed_bytes, recovered_data, N);
    }

    state.counters["Throughput"] = benchmark::Counter(state.iterations() * N * sizeof(uint32_t) / 8, benchmark::Counter::kIsRate);

    delete[] original_data;
    delete[] compressed_bytes;
    delete[] recovered_data;
}

static void BM_zigzag_encode(benchmark::State& state) {
    std::size_t N = state.range(0);

    int32_t* original_data = new int32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = (rand() - rand()) >> (rand() & 0b11111);
    }

    uint32_t* encoded_unsigend_integers = new uint32_t[N];

    for (auto _ : state) {
        streamvbyte::zigzag_encode(original_data, N, encoded_unsigend_integers);
    }

    state.counters["Throughput"] = benchmark::Counter(state.iterations() * N * sizeof(uint32_t) / 8, benchmark::Counter::kIsRate);

    delete[] original_data;
    delete[] encoded_unsigend_integers;
}

static void BM_zigzag_decode(benchmark::State& state) {
    std::size_t N = state.range(0);

    int32_t* original_data = new int32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = (rand() - rand()) >> (rand() & 0b11111);
    }

    uint32_t* encoded_unsigend_integers = new uint32_t[N];
    streamvbyte::zigzag_encode(original_data, N, encoded_unsigend_integers);

    int32_t* recovered_data = new int32_t[N];

    for (auto _ : state) {
        streamvbyte::zigzag_decode(encoded_unsigend_integers, N, recovered_data);
    }

    state.counters["Throughput"] = benchmark::Counter(state.iterations() * N * sizeof(uint32_t) / 8, benchmark::Counter::kIsRate);

    delete[] original_data;
    delete[] encoded_unsigend_integers;
    delete[] recovered_data;
}

BENCHMARK(BM_memcpy)->RangeMultiplier(2)->Range(1 << 12, 1 << 20);
BENCHMARK(BM_streamvbyte_encode)->RangeMultiplier(2)->Range(1 << 12, 1 << 20);
BENCHMARK(BM_streamvbyte_decode)->RangeMultiplier(2)->Range(1 << 12, 1 << 20);
BENCHMARK(BM_zigzag_encode)->RangeMultiplier(2)->Range(1 << 12, 1 << 20);
BENCHMARK(BM_zigzag_decode)->RangeMultiplier(2)->Range(1 << 12, 1 << 20);

BENCHMARK_MAIN();

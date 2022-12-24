#include "streamvbyte.h"
#include <gtest/gtest.h>

class StreamVByteTest : public ::testing::TestWithParam<std::size_t> { };

TEST_P(StreamVByteTest, streamvbyte) {
    std::size_t N = GetParam();

    uint32_t* original_data = new uint32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand();
    }

    uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];
    std::size_t bytes_encoded = streamvbyte::encode(original_data, N, compressed_bytes);

    uint32_t* recovered_data = new uint32_t[N];
    std::size_t bytes_decoded = streamvbyte::decode(compressed_bytes, recovered_data, N);

    ASSERT_EQ(bytes_encoded, bytes_decoded);
    for (std::size_t i = 0; i < N; ++i) {
        ASSERT_EQ(original_data[i], recovered_data[i]);
    }

    delete[] original_data;
    delete[] compressed_bytes;
    delete[] recovered_data;
}

TEST_P(StreamVByteTest, zigzag) {
    std::size_t N = GetParam();

    int32_t* original_data = new int32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() - rand();
    }

    uint32_t* encoded_unsigend_integers = new uint32_t[N];
    streamvbyte::zigzag_encode(original_data, N, encoded_unsigend_integers);

    int32_t* recovered_data = new int32_t[N];
    streamvbyte::zigzag_decode(encoded_unsigend_integers, N, recovered_data);

    for (std::size_t i = 0; i < N; ++i) {
        ASSERT_EQ(original_data[i], recovered_data[i]);
    }

    delete[] original_data;
    delete[] encoded_unsigend_integers;
    delete[] recovered_data;
}

TEST_P(StreamVByteTest, integrated) {
    std::size_t N = GetParam();

    std::vector<int32_t> original_data(N);
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() - rand();
    }

    std::vector<uint8_t> compressed_bytes = streamvbyte::encode(streamvbyte::zigzag_encode(original_data));
    std::vector<int32_t> recovered_data = streamvbyte::zigzag_decode(streamvbyte::decode(compressed_bytes, N));

    ASSERT_EQ(original_data.size(), recovered_data.size());
    for (std::size_t i = 0; i < N; ++i) {
        ASSERT_EQ(original_data[i], recovered_data[i]);
    }
}

INSTANTIATE_TEST_CASE_P(
    test, StreamVByteTest,
    ::testing::Values(
        0, 7, 8, 9, (1 << 10), (1 << 20), (1 << 20) + 2));

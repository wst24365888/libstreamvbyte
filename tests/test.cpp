#include <gtest/gtest.h>
#include "streamvbyte.h"

TEST(test, streamvbyte) {
    std::size_t N = (1 << 20) + 2;

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

TEST(test, zigzag) {
    std::size_t N = (1 << 20) + 2;

    int32_t* original_data = new int32_t[N];
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() - rand();
    }

    uint32_t* encoded_unsigend_integers = new uint32_t[N];
    streamvbyte::encode_zigzag(original_data, N, encoded_unsigend_integers);

    int32_t* recovered_data = new int32_t[N];
    streamvbyte::decode_zigzag(encoded_unsigend_integers, N, recovered_data);

    for (std::size_t i = 0; i < N; ++i) {
        ASSERT_EQ(original_data[i], recovered_data[i]);
    }

    delete[] original_data;
    delete[] encoded_unsigend_integers;
    delete[] recovered_data;
}

TEST(test, integrated) {
    std::size_t N = (1 << 20) + 2;

    std::vector<int32_t> original_data(N);
    for (std::size_t i = 0; i < N; ++i) {
        original_data[i] = rand() - rand();
    }

    std::vector<uint8_t> compressed_bytes = streamvbyte::encode(streamvbyte::encode_zigzag(original_data));
    std::vector<int32_t> recovered_data = streamvbyte::decode_zigzag(streamvbyte::decode(compressed_bytes, N));

    ASSERT_EQ(original_data.size(), recovered_data.size());
    for (std::size_t i = 0; i < N; ++i) {
        ASSERT_EQ(original_data[i], recovered_data[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
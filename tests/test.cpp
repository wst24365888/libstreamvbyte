// #include "streamvbyte.h"
// #include <assert.h>
// #include <vector>

// int main() {
//     std::size_t N = (1 << 20) + 2;

//     /* test_streamvbyte */

//     uint32_t* before_encode = new uint32_t[N];
//     for (std::size_t i = 0; i < N; i++) {
//         before_encode[i] = rand();
//     }

//     uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];
//     std::size_t bytes_encoded = streamvbyte::encode(before_encode, N, compressed_bytes);
//     std::cout << "Encoded " << bytes_encoded << " bytes" << std::endl;

//     uint32_t* after_decode = new uint32_t[N];
//     std::size_t bytes_decoded = streamvbyte::decode(compressed_bytes, after_decode, N);
//     std::cout << "Decoded " << bytes_decoded << " bytes" << std::endl;

//     assert(bytes_encoded == bytes_decoded);
//     for (std::size_t i = 0; i < N; i++) {
//         assert(before_encode[i] == after_decode[i]);
//     }

//     delete[] before_encode;
//     delete[] compressed_bytes;
//     delete[] after_decode;

//     /* test_zigzag */

//     int32_t* before_zigzag_encode = new int32_t[N];
//     for (std::size_t i = 0; i < N; i++) {
//         before_zigzag_encode[i] = rand() - rand();
//     }

//     uint32_t* after_zigzag_encode = new uint32_t[N];
//     streamvbyte::encode_zigzag(before_zigzag_encode, N, after_zigzag_encode);

//     int32_t* after_zigzag_decode = new int32_t[N];
//     streamvbyte::decode_zigzag(after_zigzag_encode, N, after_zigzag_decode);

//     for (std::size_t i = 0; i < N; i++) {
//         assert(before_zigzag_encode[i] == after_zigzag_decode[i]);
//     }

//     delete[] before_zigzag_encode;
//     delete[] after_zigzag_encode;
//     delete[] after_zigzag_decode;

//     return 0;
// }

#include <gtest/gtest.h>
#include "streamvbyte.h"

TEST(test, streamvbyte) {
    std::size_t N = (1 << 20) + 2;

    uint32_t* before_encode = new uint32_t[N];
    for (std::size_t i = 0; i < N; i++) {
        before_encode[i] = rand();
    }

    uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];
    std::size_t bytes_encoded = streamvbyte::encode(before_encode, N, compressed_bytes);

    uint32_t* after_decode = new uint32_t[N];
    std::size_t bytes_decoded = streamvbyte::decode(compressed_bytes, after_decode, N);

    ASSERT_EQ(bytes_encoded, bytes_decoded);
    for (std::size_t i = 0; i < N; i++) {
        ASSERT_EQ(before_encode[i], after_decode[i]);
    }

    delete[] before_encode;
    delete[] compressed_bytes;
    delete[] after_decode;
}

TEST(test, zigzag) {
    std::size_t N = (1 << 20) + 2;

    int32_t* before_zigzag_encode = new int32_t[N];
    for (std::size_t i = 0; i < N; i++) {
        before_zigzag_encode[i] = rand() - rand();
    }

    uint32_t* after_zigzag_encode = new uint32_t[N];
    streamvbyte::encode_zigzag(before_zigzag_encode, N, after_zigzag_encode);

    int32_t* after_zigzag_decode = new int32_t[N];
    streamvbyte::decode_zigzag(after_zigzag_encode, N, after_zigzag_decode);

    for (std::size_t i = 0; i < N; i++) {
        ASSERT_EQ(before_zigzag_encode[i], after_zigzag_decode[i]);
    }

    delete[] before_zigzag_encode;
    delete[] after_zigzag_encode;
    delete[] after_zigzag_decode;
}

TEST(test, integrated) {
    std::size_t N = (1 << 20) + 2;

    std::vector<int32_t> original_data(N);
    for (std::size_t i = 0; i < N; i++) {
        original_data[i] = rand() - rand();
    }

    std::vector<uint32_t> zigzag_encoded_data = streamvbyte::encode_zigzag(original_data);
    std::vector<uint8_t> streamvbyte_encoded_data = streamvbyte::encode(zigzag_encoded_data);

    std::vector<uint32_t> streamvbyte_decoded_data = streamvbyte::decode(streamvbyte_encoded_data, N);
    std::vector<int32_t> zigzag_decoded_data = streamvbyte::decode_zigzag(streamvbyte_decoded_data);

    ASSERT_EQ(original_data.size(), zigzag_decoded_data.size());
    for (std::size_t i = 0; i < N; i++) {
        ASSERT_EQ(original_data[i], zigzag_decoded_data[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
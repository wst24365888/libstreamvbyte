#include "streamvbyte.h"
#include <assert.h>

int main() {
    std::size_t N = (1 << 20) + 2;

    uint32_t* before_encode = new uint32_t[N];
    for (std::size_t i = 0; i < N; i++) {
        before_encode[i] = rand();
    }

    uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];
    std::size_t bytes_encoded = streamvbyte::encode(before_encode, N, compressed_bytes);
    std::cout << "Encoded " << bytes_encoded << " bytes" << std::endl;

    uint32_t* after_decode = new uint32_t[N];
    std::size_t bytes_decoded = streamvbyte::decode(compressed_bytes, after_decode, N);
    std::cout << "Decoded " << bytes_decoded << " bytes" << std::endl;

    assert(bytes_encoded == bytes_decoded);
    for (std::size_t i = 0; i < N; i++) {
        assert(before_encode[i] == after_decode[i]);
    }

    delete[] before_encode;
    delete[] compressed_bytes;
    delete[] after_decode;

    int32_t* before_zigzag_encode = new int32_t[N];
    for (std::size_t i = 0; i < N; i++) {
        before_zigzag_encode[i] = rand() - rand();
    }

    uint32_t* after_zigzag_encode = new uint32_t[N];
    streamvbyte::encode_zigzag(before_zigzag_encode, N, after_zigzag_encode);

    int32_t* after_zigzag_decode = new int32_t[N];
    streamvbyte::decode_zigzag(after_zigzag_encode, N, after_zigzag_decode);

    for (std::size_t i = 0; i < N; i++) {
        assert(before_zigzag_encode[i] == after_zigzag_decode[i]);
    }

    return 0;
}
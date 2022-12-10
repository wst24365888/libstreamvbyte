#include "streamvbyte.h"
#include <assert.h>

int main() {
    std::size_t N = (1 << 20) + 2;

    uint32_t* before_encode = new uint32_t[N];
    for (std::size_t i = 0; i < N; i++) {
        before_encode[i] = rand();
    }
    // for (std::size_t i = 0; i < N; i++) {
    //     std::cout << (int)before_encode[i] << " ";
    // }
    // std::cout << std::endl;

    uint8_t* compressed_bytes = new uint8_t[streamvbyte::max_compressed_size(N)];

    std::size_t bytes_encoded = streamvbyte::encode(before_encode, N, compressed_bytes);
    std::cout << "Encoded " << bytes_encoded << " bytes" << std::endl;
    // for (std::size_t i = 0; i < bytes_encoded; i++) {
    //     std::cout << (int)compressed_bytes[i] << " ";
    // }
    // std::cout << std::endl;

    uint32_t* after_decode = new uint32_t[N];

    std::size_t bytes_decoded = streamvbyte::decode(compressed_bytes, after_decode, N);
    std::cout << "Decoded " << bytes_decoded << " bytes" << std::endl;
    // for (std::size_t i = 0; i < N; i++) {
    //     std::cout << (int)after_decode[i] << " ";
    // }
    // std::cout << std::endl;

    assert(bytes_encoded == bytes_decoded);
    for (std::size_t i = 0; i < N; i++) {
        // std::cout << i << " / " << N << ": " << before_encode[i] << " " << after_decode[i] << std::endl;
        assert(before_encode[i] == after_decode[i]);
    }

    delete[] before_encode;
    delete[] compressed_bytes;
    delete[] after_decode;

    return 0;
}
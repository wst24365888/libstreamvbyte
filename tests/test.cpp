#include "streamvbyte.h"
#include <assert.h>

int main() {
    std::size_t N = 1 << 30;

    uint32_t* before_encode = (uint32_t*)malloc(N * sizeof(uint32_t));
    for (std::size_t i = 0; i < N; i++) {
        before_encode[i] = rand();
    }
    // for (std::size_t i = 0; i < 10; i++) {
    //     std::cout << (int)before_encode[i] << " ";
    // }
    // std::cout << std::endl;

    uint8_t* compressed = (uint8_t*)malloc(N * 4 * sizeof(uint32_t));

    std::size_t bytes_encoded = streamvbyte::encode(before_encode, N, compressed);
    std::cout << "Encoded " << bytes_encoded << " bytes" << std::endl;
    // for (std::size_t i = 0; i < 10; i++) {
    //     std::cout << (int)compressed[i] << " ";
    // }
    // std::cout << std::endl;
    
    free(before_encode);

    uint32_t* after_decode = (uint32_t*)malloc(N * sizeof(uint32_t));

    std::size_t bytes_decoded = streamvbyte::decode(compressed, after_decode, N);
    std::cout << "Decoded " << bytes_decoded << " bytes" << std::endl;
    // for (std::size_t i = 0; i < 10; i++) {
    //     std::cout << (int)after_decode[i] << " ";
    // }
    // std::cout << std::endl;

    free(compressed);
    free(after_decode);

    assert(bytes_encoded == bytes_decoded);

    return 0;
}
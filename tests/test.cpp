#include "streamvbyte.h"

int main() {
    std::size_t N = 7777;

    uint32_t* in = (uint32_t*)malloc(N * sizeof(uint32_t));
    for (std::size_t i = 0; i < N; i++) {
        in[i] = rand();
    }

    uint8_t* out = (uint8_t*)malloc(N * 4 * sizeof(uint32_t));

    std::size_t count = streamvbyte::encode(in, N, out);
    std::cout << "Encoded " << count << " bytes" << std::endl;
    // for (std::size_t i = 0; i < count; i++) {
    //     std::cout << (int)out[i] << " ";
    // }
    // std::cout << std::endl;

    free(in);
    free(out);

    return 0;
}
#include "streamvbyte.h"

int main() {
    std::size_t N = 8;

    uint32_t* in = new uint32_t[N];
    for (std::size_t i = 0; i < N; i++) {
        in[i] = rand();
    }

    uint8_t* out = new uint8_t[N*4];

    std::size_t count = streamvbyte::encode(in, N, out);
    for (std::size_t i = 0; i < count; i++) {
        std::cout << (int)out[i] << " ";
    }
    std::cout << std::endl;

    delete[] in;
    delete[] out;

    return 0;
}
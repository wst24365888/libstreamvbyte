#include <iostream>

namespace stringvbyte {
/*
    Encodes a sequence of 32-bit unsigned integers to a byte array.

    @param in: a sequence of 32-bit unsigned integers
    @param count: the number of unsigned integers to encode
    @param out: a byte array

    @return the number of bytes written to out
*/
std::size_t encode(const uint32_t* in, std::size_t count, uint8_t* out);

/*
    Decodes a sequence of 32-bit unsigned integers from a byte array.

    @param in: a byte array
    @param out: a sequence of 32-bit unsigned integers
    @param count: the number of unsigned integers to decode

    @return the number of bytes written to in
*/
std::size_t decode(const uint8_t* in, uint32_t* out, std::size_t count);
}
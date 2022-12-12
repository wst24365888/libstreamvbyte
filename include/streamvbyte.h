#pragma once

#include <iostream>
#include <vector>

namespace streamvbyte {
/*
    Encodes a sequence of 32-bit unsigned integers to a byte array.

    @param in: a sequence of 32-bit unsigned integers
    @param count: the number of unsigned integers to encode
    @param out: a byte array

    @return the number of bytes written to out
*/
std::size_t encode(const uint32_t* in, std::size_t count, uint8_t* out);

/*
    Encodes a sequence of 32-bit unsigned integers to a byte array.

    @param in: a vector of 32-bit unsigned integers

    @return the number of bytes written to out
*/
std::vector<uint8_t> encode(const std::vector<uint32_t>& in);

/*
    Decodes a sequence of 32-bit unsigned integers from a byte array.

    @param in: a byte array
    @param out: a sequence of 32-bit unsigned integers
    @param count: the number of unsigned integers to decode

    @return the number of bytes written to in
*/
std::size_t decode(const uint8_t* in, uint32_t* out, std::size_t count);

/*
    Decodes a sequence of 32-bit unsigned integers from a byte array.

    @param in: a vector of bytes
    @param count: the number of unsigned integers to decode

    @return the number of bytes written to in
*/
std::vector<uint32_t> decode(const std::vector<uint8_t>& in, std::size_t count);

/*
    Returns the maximum number of bytes that can be written by encode().

    @param size: the number of unsigned integers to encode

    @return the maximum number of bytes that can be written by encode()
*/
static inline size_t max_compressed_size(const uint32_t size) {
    return (size + 3) / 4 + size * sizeof(uint32_t);
}

/*
    Encode a sequence of 32-bit signed integers to a sequence of 32-bit unsigned integers.

    @param in: a sequence of 32-bit signed integers
    @param count: the number of signed integers to encode
    @param out: a sequence of 32-bit unsigned integers
*/
void zigzag_encode(const int32_t* in, std::size_t count, uint32_t* out);

/*
    Encode a vector of 32-bit signed integers to a vector of 32-bit unsigned integers.

    @param in: a vector of 32-bit signed integers

    @return a vector of 32-bit unsigned integers
*/
std::vector<uint32_t> zigzag_encode(const std::vector<int32_t>& in);

/*
    Decode a sequence of 32-bit unsigned integers to a sequence of 32-bit signed integers.

    @param in: a sequence of 32-bit unsigned integers
    @param count: the number of unsigned integers to decode
    @param out: a sequence of 32-bit signed integers
*/
void zigzag_decode(const uint32_t* in, std::size_t count, int32_t* out);

/*
    Decode a vector of 32-bit unsigned integers to a vector of 32-bit signed integers.

    @param in: a vector of 32-bit unsigned integers

    @return a vector of 32-bit signed integers
*/
std::vector<int32_t> zigzag_decode(const std::vector<uint32_t>& in);
}
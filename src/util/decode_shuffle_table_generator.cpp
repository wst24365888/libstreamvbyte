#include <iomanip>
#include <iostream>

int main() {
    std::cout << "static const uint8_t decode_shffule_table[256*16] = {" << std::endl;

    for (std::size_t fourth_block_length = 0b00; fourth_block_length <= 0b11; ++fourth_block_length) {
        for (std::size_t third_block_length = 0b00; third_block_length <= 0b11; ++third_block_length) {
            for (std::size_t second_block_length = 0b00; second_block_length <= 0b11; ++second_block_length) {
                for (std::size_t first_block_length = 0b00; first_block_length <= 0b11; ++first_block_length) {
                    std::cout << "\t";

                    uint8_t counter = 0x00;

                    for (std::size_t i = 0; i < 4; ++i) {
                        if (i > first_block_length) {
                            std::cout << "0xFF, ";
                            continue;
                        }

                        std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(counter) << ", ";
                        counter += 0x01;
                    }

                    for (std::size_t i = 0; i < 4; ++i) {
                        if (i > second_block_length) {
                            std::cout << "0xFF, ";
                            continue;
                        }

                        std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(counter) << ", ";
                        counter += 0x01;
                    }

                    for (std::size_t i = 0; i < 4; ++i) {
                        if (i > third_block_length) {
                            std::cout << "0xFF, ";
                            continue;
                        }

                        std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(counter) << ", ";
                        counter += 0x01;
                    }

                    for (std::size_t i = 0; i < 4; ++i) {
                        if (i > fourth_block_length) {
                            std::cout << "0xFF, ";
                            continue;
                        }

                        std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(counter) << ", ";
                        counter += 0x01;
                    }

                    std::cout << " // " << first_block_length << second_block_length << third_block_length << fourth_block_length << std::endl;
                }
            }
        }
    }

    std::cout << "};" << std::endl;

    return -0;
}
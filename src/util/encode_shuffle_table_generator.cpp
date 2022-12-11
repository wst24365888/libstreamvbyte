#include <iomanip>
#include <iostream>

int main() {
    std::cout << "static const uint8_t encode_shffule_table[64*16] = {" << std::endl;

    for (std::size_t third_block_length = 1; third_block_length <= 4; ++third_block_length) {
        for (std::size_t second_block_length = 1; second_block_length <= 4; ++second_block_length) {
            for (std::size_t first_block_length = 1; first_block_length <= 4; ++first_block_length) {
                std::cout << "\t";

                uint8_t first_block_first_value = 0x00;
                for (std::size_t i = 1; i <= first_block_length; ++i) {
                    std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(first_block_first_value) << ", ";
                    first_block_first_value += 0x01;
                }

                uint8_t second_block_first_value = 0x04;
                for (std::size_t i = 1; i <= second_block_length; ++i) {
                    std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(second_block_first_value) << ", ";
                    second_block_first_value += 0x01;
                }

                uint8_t third_block_first_value = 0x08;
                for (std::size_t i = 1; i <= third_block_length; ++i) {
                    std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(third_block_first_value) << ", ";
                    third_block_first_value += 0x01;
                }

                uint8_t fourth_block_first_value = 0x0C;
                for (std::size_t i = 0; i < 4; ++i) {
                    std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(fourth_block_first_value) << ", ";
                    fourth_block_first_value += 0x01;
                }

                for (std::size_t i = 0; i < 12 - first_block_length - second_block_length - third_block_length; ++i) {
                    std::cout << "0xFF, ";
                }

                std::cout << "// " << first_block_length << second_block_length << third_block_length << "1~" << first_block_length << second_block_length << third_block_length << "4" << std::endl;
            }
        }
    }

    std::cout << "};" << std::endl;

    return 0;
}
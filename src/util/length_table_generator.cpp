#include <iostream>

int main() {
    std::cout << "static uint8_t length_table[256] = {" << std::endl;

    for (int fourth = 1; fourth <= 4; ++fourth) {
        for (int third = 1; third <= 4; ++third) {
            for (int second = 1; second <= 4; ++second) {
                for (int first = 1; first <= 4; ++first) {
                    std::cout << "\t" << first + second + third + fourth << ", //" << first << second << third << fourth << std::endl;
                }
            }
        }
    }

    std::cout << "};" << std::endl;

    return 0;
}
#include <iostream>
#include <chrono>

unsigned int baseTwoDigits(unsigned int x) {
    return x ? 32 - __builtin_clz(x) : 0;
}

static unsigned int baseTenDigits(unsigned int x) {
    static const unsigned char guess[33] = {
        0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
        9, 9, 9
    };
    static const unsigned int tenToThe[] = {
        1, 10, 100, 1000, 10000, 100000,
        1000000, 10000000, 100000000, 1000000000,
    };
    unsigned int digits = guess[baseTwoDigits(x)];
    return digits + (x >= tenToThe[digits]);
}


// SEP

uint_fast8_t baseTwoDigitsUint8(unsigned int x) {
    return x ? 32 - __builtin_clz(x) : 0;
}

static uint_fast8_t baseTenDigitsUnit8(unsigned int x) {
    static const unsigned char guessU[33] = {
        0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
        9, 9, 9
    };
    static const uint_fast64_t tenToTheU[] = {
        1, 10, 100, 1000, 10000, 100000,
        1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000,
    };
    uint_fast8_t digits = guessU[baseTwoDigitsUint8(x)];
    return digits + (x >= tenToTheU[digits]);
}

int main() {
    int test;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    begin = std::chrono::steady_clock::now();
    test = baseTenDigits(179832);
    end = std::chrono::steady_clock::now();
    std::cout << test << std::endl;
    std::cout << "Elapsed time unsigned: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[μs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    test = baseTenDigitsUnit8(179832);
    end = std::chrono::steady_clock::now();
    std::cout << test << std::endl;
    std::cout << "Elapsed time time uint8_t: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[μs]" << std::endl;
}
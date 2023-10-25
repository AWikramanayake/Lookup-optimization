// ATTEMPTING TO CREATE A

#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

unsigned int baseTwoDigits(unsigned int x) {
    return x ? 32 - __builtin_clz(x) : 0;
}

static unsigned int baseTenDigits(unsigned int x) {
    static const unsigned char guess[65] = {
        0 ,0 ,0 ,0 , 1 ,1 ,1 , 2 ,2 ,2 ,
        3 ,3 ,3 ,3 , 4 ,4 ,4 , 5 ,5 ,5 ,
        6 ,6 ,6 ,6 , 7 ,7 ,7 , 8 ,8 ,8 ,
        9 ,9 ,9 ,9 , 10,10,10, 11,11,11,
        12,12,12,12, 13,13,13, 14,14,14,
        15,15,15,15, 16,16,16, 17,17,17,
        18,18,18,18, 19
    };
    static const long unsigned int tenToThe[] = {
        1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
        1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000,
        1000000000000000, 10000000000000000, 100000000000000000, 1000000000000000000, 10000000000000000000,
    };
    unsigned int digits = guess[baseTwoDigits(x)];
    return digits + (x >= tenToThe[digits]);
}


// SEP

uint_fast8_t baseTwoDigitsUint8(unsigned int x) {
    return x ? 32 - __builtin_clz(x) : 0;
}

static uint_fast8_t baseTenDigitsUint8(unsigned int x) {
    static const unsigned char guessU[65] = {
        0 ,0 ,0 ,0 , 1 ,1 ,1 , 2 ,2 ,2 ,
        3 ,3 ,3 ,3 , 4 ,4 ,4 , 5 ,5 ,5 ,
        6 ,6 ,6 ,6 , 7 ,7 ,7 , 8 ,8 ,8 ,
        9 ,9 ,9 ,9 , 10,10,10, 11,11,11,
        12,12,12,12, 13,13,13, 14,14,14,
        15,15,15,15, 16,16,16, 17,17,17,
        18,18,18,18, 19
    };
    static const uint_fast64_t tenToTheU[] = {
        1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
        1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000,
        1000000000000000, 10000000000000000, 100000000000000000, 1000000000000000000, 10000000000000000000,
    };
    uint_fast8_t digits = guessU[baseTwoDigitsUint8(x)];
    return digits + (x >= tenToTheU[digits]);
}

int main() {
    int test, line_num, mismatches = 0;
    int cmath_res[1000], lookup_res[1000], lookupU8_res[1000];
    uint64_t num;
    uint64_t arr[10000];
    std::string line;
    std::ifstream InFile;
    InFile.open("test_numlist.csv");
    std::getline(InFile, line);
    while (line_num < 10000 && InFile >> num) {
        arr[line_num] = num;
        line_num++;
    }

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    uint64_t total_time = 0;

    begin = std::chrono::steady_clock::now();
    test = log10(179832);
    end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time cmath log10: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    begin = std::chrono::steady_clock::now();
    test = baseTenDigits(179832);
    end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time lookup table unsigned int: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    begin = std::chrono::steady_clock::now();
    test = baseTenDigitsUint8(179832);
    end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time lookup table uint_fast8_t: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    total_time = 0;

    for (int i = 0; i < 1000; i++) {
        test = log10(arr[i]);
        cmath_res[i] = test+1;
    }

    for (int i = 0; i < 1000; i++) {
        begin = std::chrono::steady_clock::now();
        test = baseTenDigits(arr[i]);
        end = std::chrono::steady_clock::now();
        total_time = total_time + (std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count());
        lookup_res[i] = test;
    }
    std::cout << "Elapsed time for 1000 attempts with lookup table unsigned int: " << total_time << "[ns]" << std::endl;

    total_time = 0;

    for (int i = 0; i < 1000; i++) {
        begin = std::chrono::steady_clock::now();
        test = baseTenDigitsUint8(arr[i]);
        end = std::chrono::steady_clock::now();
        total_time = total_time + (std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count());
        lookupU8_res[i] = test;
    }
    std::cout << "Elapsed time for 1000 attempts with lookup table uint8_t: " << total_time << "[ns]" << std::endl;

    for (int i = 0; i < 1000; i++) {
        if (!(cmath_res[i] == lookup_res[i] && cmath_res[i] == lookupU8_res[i])) {
            mismatches++;
            // std::cout << cmath_res[i] << " " << lookup_res[i] << " " << lookupU8_res[i] << " " << arr[i] << std::endl;
        }
    }
    std::cout << "Mismatches: " << mismatches << std::endl;

}

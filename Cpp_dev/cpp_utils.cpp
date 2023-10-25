#include <string>
#include <vector>
#include <fstream>
#include <cmath>       /* log10 */

class DataList {
    public:
        std::vector<int> list_data;
        int list_len;
        std::string list_name;
        bool skip_header;
        void setListSize() {
            list_data.resize(list_len);
        };
};

void readList(DataList ListObj) {
    int line_num = 0;
    int num;
    std::ifstream InFile;
    InFile.open(ListObj.list_name);
    std::cout << "Reading list " << ListObj.list_name << std::endl;
    while (line_num < ListObj.list_len && InFile >> num) {
        ListObj.list_data[line_num] = num;
    };
};

uint_fast8_t baseTwoDigits(unsigned int x) {
    return x ? 32 - __builtin_clz(x) : 0;
}

static uint_fast8_t baseTenDigits(unsigned int x) {
    static const unsigned char guess[33] = {
        0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
        9, 9, 9
    };
    static const uint_fast64_t tenToThe[] = {
        1, 10, 100, 1000, 10000, 100000,
        1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000,
    };
    uint_fast8_t digits = guess[baseTwoDigits(x)];
    return digits + (x >= tenToThe[digits]);
};

static uint_fast64_t quick_pow10(uint_fast8_t n)
{
    static uint_fast64_t pow10[15] = {
        1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
        1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000,
    };

    return pow10[n];
}

void findListMatches(DataList ID_List, DataList Test_Seqs) {
};

std::vector<std::vector<uint_fast64_t> > findSingleMatches(DataList ID_List, int test_sequence) {
    std::vector<std::vector<uint_fast64_t> > matches;
    uint_fast8_t numdigits, divisor1, divisor2, num_matches;
    uint_fast64_t n, out;
    numdigits = baseTenDigits(test_sequence);
    divisor1 = quick_pow10(numdigits);
    divisor2 = quick_pow10(numdigits-1);
    num_matches = 0;
    for (int i = 0; i < ID_List.list_len; i++) {
        n = ID_List.list_data[i];
        while(n != 0) {
            out = n % divisor1;
            n = (n / 10);
            if (out == test_sequence) {
                matches.push_back(std::vector<uint_fast64_t>());
                matches[num_matches].push_back(out);
                matches[num_matches].push_back(test_sequence);
                num_matches++;
            }
            if (n < divisor2) {
                continue;
            }
        }
    }
    std::cout << "Match search completed\n";

    if (num_matches == 0) {
        std::cout << "No matches found\n";
    }
    else {
        std::cout << "Matches: \n";
        for (int i = 0; i < num_matches; i++) {
            std::cout << matches[i][0] << ", " << matches[i][1] << "\n";
        }
    }
    return matches;
}
// IN CONSTRUCTION: CUDA C++ IMPLEMENTATION OF THE LOOP
// STEPS: IMPLEMENT WITH REGULAR C++ --> ADD PARALLELIZATION

// NEED TO MOVE FUNCTIONS TO EXTERNAL FILE
// FIND MATCHES FCT NEEDS TO BE DEBUGGED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
// #include "cpp_utils.h"
#include <cmath>       /* log10 */

class DataList {
    public:
        std::vector<unsigned int> list_data;
        int list_len;
        std::string list_name;
        bool skip_header;
        void setListSize() {
            list_data.resize(list_len);
        };
};

std::vector<unsigned int> readList(DataList ListObj) {
    std::vector<unsigned int> outlist;
    outlist.resize(ListObj.list_len);
    int line_num = 0;
    uint64_t num;
    std::ifstream InFile;
    InFile.open(ListObj.list_name);
    if (ListObj.skip_header == true) {
        std::string line;
        std::getline(InFile, line);
        std::cout << "skipped line\n";
    }
    std::cout << "Reading list " << ListObj.list_name << std::endl;
    while (line_num < ListObj.list_len && InFile >> num) {
        outlist[line_num] = num;
        line_num++;
    }
    return outlist;
};

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

void findListMatches(DataList ID_List, DataList Test_Seqs) {
};

std::vector<std::vector<uint_fast64_t> > findSingleMatches(DataList ID_List, int test_sequence) {
    std::vector<std::vector<uint_fast64_t> > matches;
    uint_fast64_t numdigits, divisor1, divisor2, num_matches;
    uint_fast64_t n, out;
    // NEEDS FURTHER DEBUGGING
    // numdigits = baseTenDigits(test_sequence) + 1;
    numdigits = log10(test_sequence) + 1;
    divisor1 = pow(10, numdigits);
    divisor2 = pow(10, numdigits-1);
    num_matches = 0;
    for (int i = 0; i < ID_List.list_len; i++) {
        n = ID_List.list_data[i];
        while(n != 0) {
            out = n % divisor1;
            n = (n / 10);
            if (out == test_sequence) {
                matches.push_back(std::vector<uint_fast64_t>());
                matches[num_matches].push_back(test_sequence);
                matches[num_matches].push_back(ID_List.list_data[i]);
                num_matches++;
            }
            if (n < divisor2) {
                break;
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
        std::cout << "# of matches: " << num_matches << "\n";
    }
    return matches;
}

int main() {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    bool many_seq;
    DataList wayList;
    DataList seqList;
    unsigned int testseq;

    std::cout << "Enter Way ID list filename\n";
    std::cin >> wayList.list_name;
    std::cout << "Enter length of Way ID list\n";
    std::cin >> wayList.list_len;
    std::cout << "Skip a line for column header?\n1 -> Skip, 0 -> Don't skip\n";
    std::cin >> wayList.skip_header;
    std::cout << "Input a list of test sequences? Else: manually input a single test sequence\n";
    std::cout << "1 -> list of sequences, 0 -> single sequence\n";
    std::cin >> many_seq;
    if (many_seq == false) {
        std::cout << "Enter integer sequence to search for\n";
        std::cin >> testseq;
    }
    else if (many_seq == true) {
        std::cout << "Enter filename of list of sequences\n";
        std::cin >> seqList.list_name;
        std::cout << "Enter length of the list or the number of values to read\n";
        std::cin >> seqList.list_len;
        std::cout << "Skip a line for column header?\n1 -> Skip, 0 -> Don't skip\n";
        std::cin >> seqList.skip_header;
    }

    /*
    //DEBUG
    wayList.list_name = "test_numlist.csv";
    wayList.list_len = 100000;
    wayList.skip_header = true;
    many_seq = false;
    testseq = 60235;
    */


    std::cout << "Program has begun" << std::endl;

    wayList.setListSize();

    std::cout << "Reads have begun\n";
    begin = std::chrono::steady_clock::now();
    wayList.list_data = readList(wayList);

    if (many_seq == false) {
        end = std::chrono::steady_clock::now();
        std::vector<std::vector<uint_fast64_t> > single_matches;
        std::cout << "Elapsed time for list read: " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[μs]" << std::endl;
        std::cout << "Search for matches has begun\n";
        begin = std::chrono::steady_clock::now();
        single_matches = findSingleMatches(wayList, testseq);
        end = std::chrono::steady_clock::now();
    }

    if (many_seq == true) {
        seqList.setListSize();
        readList(seqList);
        end = std::chrono::steady_clock::now();
        std::cout << "Combined elapsed read time for both lists: " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[μs]" << std::endl;
        std::cout << "Search for matches has begun";
        begin = std::chrono::steady_clock::now();
        // CALL FIND MATCHES ON SEQUENCE LIST HERE
        end = std::chrono::steady_clock::now();
    }

    std::cout << "Elapsed search time: " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() << "[μs]" << std::endl;
}


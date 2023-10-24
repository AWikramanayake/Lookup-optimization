// IN CONSTRUCTION: CUDA C++ IMPLEMENTATION OF THE LOOP
// STEPS: IMPLEMENT WITH REGULAR C++ --> ADD PARALLELIZATION


/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

class DataList {
    public:
        std::vector<int> lis_data;
        int list_len;
        string list_name;
        // bool skip;
        void set_listsize() {
            list_data.resize(list_len)
        }
}

int main() {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    bool single_seq
    DataList wayList;

    std::cout << "Enter Way ID list filename\n";
    std::cin >> wayList.list_name;
    std::cout << "Enter length of Way ID list\n";
    std::cin >> wayList.list_len;
    std::cout >> "Input a list of test sequences? Else: manually input a single test sequence\n";
    std::cout >> "true -> list of sequences, false -> single sequence\n";
    std::cin >> single_seq;
    if (single_seq == false) {
        int testseq;
        std::cout >> "Enter integer sequence to search for\n";
        std::cin >> testseq;
    }
    else if (single_seq == true) {
        DataList seqList;
        std::cout << "Enter filename of list of sequences\n";
        std::cin >> seqList.list_name;
        std::cout << "Enter length of the list\n";
        std::cin >> seqList_list_len;
    }

    std::cout << "Program has begun" << endl;

    wayList.set_listsize();

    std::cout << "Reads have begun\n";
    begin = std::chrono::steady_clock::now();
    // CALL LIST READ ON W_IDs HERE

    if (single_seq == false) {
        end = std::chrono::steady_clock::now();
        std::cout << "Elapsed time for list read: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
        std::cout << "Search for matches has begun";
        begin = std::chrono::steady_clock::now();
        // CALL FIND MATCHES ON SINGLE SEQUENCE HERE
        end = std::chrono::steady_clock::now();
    }

    if (single_seq == true) {
        seqList.set_listsize();
        // CALL LISTREAD ON TEST SEQUENCE LIST HERE
        end = std::chrono::steady_clock::now();
        std::cout << "Combined elapsed read time for both lists: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
        std::cout << "Search for matches has begun";
        begin = std::chrono::steady_clock::now();
        // CALL FIND MATCHES ON SEQUENCE LIST HERE
        end = std::chrono::steady_clock::now();
    }

    std::cout << "Elapsed search time: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
}

*/


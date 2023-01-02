#include <iostream>
#include "simulator.hpp"
#include "turing_parser.hpp"

using namespace std;

int main(int argc, char* argv[]){
    bool is_verbose = false;
    std::string tm_path = "";
    std::string input = "";
    if (argc > 1) {
        if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
            std::cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << std::endl;
            return 0;
        } else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--verbose")) {
            is_verbose = true;
            if (argc != 4) {
                std::cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << std::endl;
                return 0;
            }
            tm_path = argv[2];
            input = argv[3];
        } else {
            if (argc != 3) {
                std::cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << std::endl;
                return 0;
            }
            tm_path = argv[1];
            input = argv[2];
        }
        simulator tm_simulator(tm_path, input, is_verbose);
        tm_simulator.check_if_legal(input, is_verbose);
        tm_simulator.run_turing(is_verbose);
    } else {
        std::cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << std::endl;
        return 0;
    }
    return 0;
}
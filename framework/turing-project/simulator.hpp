#ifndef SIM_H
#define SIM_H

# include <iostream>
#include <iterator>
#include <new>
# include <vector>
# include <deque>
# include <string>
# include <cstring>
# include <set>
# include <sstream>
#include <fstream>

# include "turing_parser.hpp"

class simulator {
    private:
        turing_machine tm;
        std::vector<std::deque<char>> tape{};
        int steps;
        std::string cur_state;
        std::vector<int> zero_positions;
        std::vector<int> heads{};
        std::vector<int> verbose_index{};
        int start;
        int end;
        bool is_active;
        bool is_legal;

    public:
        simulator(std::string tm_path, std::string input, bool is_verbose)
        :tm(),
        steps(0),
        cur_state(""),
        start(0),
        end(0),
        is_active(true),
        is_legal(true)
        {
            parse_turing(tm_path, is_verbose);
            int N = tm.get_tape_num();
            for (int i = 0; i < N; i ++) {
                std::deque<char> tap{};
                tape.push_back(tap);
            }
            if (input.size() != 0) {
                for (int i = 0; i < input.size(); i++)
                {
                    tape.at(0).push_back(input.at(i));
                }
            } else {
                tape.at(0).push_back('_');
            }
            for (int i = 1; i < N; i ++) {
                tape.at(i).push_back('_');
            }
            cur_state = tm.get_q0();
            zero_positions.resize(N, 0);
            heads.resize(N, 0);
        }
        void parse_turing(std::string tm_path, bool is_verbose);

        void check_if_legal(std::string input, bool is_verbose);

        void deque_push_front(int tape_index, char elem);

        void move_heads(std::vector<dir> &dirs);

        bool is_equal_syms(std::vector<char> tape_sym, std::vector<char> trans_sym);

        bool transition();

        void print_tape_index(int tape_index, int zero_pos);

        void print_tape(int tape_index);

        void print_verbose_tape(int tape_index);

        void print_head(int head_pos);

        void print_verbose();

        void run_turing(bool is_verbose);
};

# endif
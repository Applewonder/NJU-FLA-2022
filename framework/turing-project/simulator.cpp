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
# include "simulator.hpp"


void simulator::parse_turing(std::string tm_path, bool is_verbose) {
    std::ifstream infile;
    infile.open(tm_path, std::ios::in);
    if (!infile.is_open())
    {
        std::cerr << "wrong file path" << std::endl;
        exit(-1);
    }
    std::string s;
    int fill_part = 0;
    int line_count = 1;
    while (getline(infile, s))
    {
        std::string precessed_line = tm.preprocess_string(s, is_verbose, line_count);
        if (precessed_line.size() != 0) {
            if (fill_part < 7) {
                if (precessed_line.at(0) == '#') {
                    if (precessed_line.at(1) == 'Q') {
                        tm.fill_Q(precessed_line, is_verbose, line_count);
                        fill_part ++;
                    } else if (precessed_line.at(1) == 'S') {
                        tm.fill_S(precessed_line, is_verbose, line_count);
                        fill_part ++;
                    } else if (precessed_line.at(1) == 'G') {
                        tm.fill_G(precessed_line, is_verbose, line_count);
                        fill_part ++;
                    } else if (precessed_line.at(1) == 'q') {
                        tm.fill_q0(precessed_line, is_verbose, line_count);
                        fill_part ++;
                    } else if (precessed_line.at(1) == 'B') {
                        tm.fill_B(precessed_line, is_verbose, line_count);
                        fill_part ++;
                    } else if (precessed_line.at(1) == 'F') {
                        tm.fill_F(precessed_line, is_verbose, line_count);
                        fill_part ++;
                    } else if (precessed_line.at(1) == 'N') {
                        tm.fill_N(precessed_line, is_verbose, line_count);
                        fill_part ++;
                    } else {
                        if (is_verbose) {
                            std::cerr << "line " << line_count << "error" << std::endl;
                            exit(-1);
                        } else {
                            std::cerr << "syntax error" << std::endl;
                            exit(-1);
                        }
                    }
                } else {
                    if (is_verbose) {
                        std::cerr << "line " << line_count << "error" << std::endl;
                        exit(-1);
                    } else {
                        std::cerr << "syntax error" << std::endl;
                        exit(-1);
                    }
                }
            } else {
                tm.fill_delta(s, is_verbose, line_count);
            }
        }
        line_count ++;
    }
}

void simulator::check_if_legal(std::string input, bool is_verbose) {
    for (int i = 0; i < input.size(); i++) {
        char sym = input.at(i);
        std::set<char> S = tm.get_S();
        if (S.find(sym) == S.end()) {
            if (is_verbose) {
                std:: cerr << "Input: " << input << std::endl;
                std:: cerr << "==================== ERR ====================" << std::endl;
                std:: cerr << "error: '" << sym << "' was not declared in the set of input symbols" << std::endl;
                std:: cerr << "Input: " << input << std::endl;
                std:: cerr << "       ";
                for (int j = 0; j < i; j++)
                {
                    std::cerr << " ";
                }
                std:: cerr << "^" << std::endl;
                std::cerr << "==================== END ====================" << std::endl;
            } else {
                std::cerr << "illegal input" << std::endl;
            }
            exit(-1);
        };
    }
    if (is_verbose) {
        std::cout << "Input: " << input << std::endl;
        std::cout << "==================== RUN ====================" << std::endl;
    }
}

void simulator::deque_push_front(int tape_index, char elem) {
    tape.at(tape_index).push_front(elem);
    zero_positions.at(tape_index) ++;
}

void simulator::move_heads(std::vector<dir> &dirs) {
    for (int i = 0; i < dirs.size(); i ++) {
        int direction = dirs.at(i);
        int index = heads.at(i);
        switch (direction) {
            case dir::LEFT: {
                if (index == 0) {
                    deque_push_front(i, '_');
                } else {
                    heads.at(i) --;
                }
                break;
            }
            case dir::RIGHT: {
                if (index == tape.at(i).size() - 1) {
                    tape.at(i).push_back('_');
                } 
                heads.at(i) ++;
                break;
            }
            case dir::STAY: {
                break;
            }
        }
    }
}

bool simulator::is_equal_syms(std::vector<char> tape_sym, std::vector<char> trans_sym) {
    int size = tape_sym.size();
    if (trans_sym.size() != size) {
        std::cerr << "NOOOOOOOO I'm in is_equal_syms" << std::endl;
        return false;
    }
    for (int i = 0; i < size; i ++) {
        if (trans_sym.at(i) == '*' && (tape_sym.at(i) != '_')) continue;
        if (trans_sym.at(i) != tape_sym.at(i)) {
            return false;
        }
    }
    return true;
}

bool simulator::transition() {
    int N = tm.get_tape_num();
    std::vector<char> old_syms(N);
    for (int i = 0; i < N; i ++) {
        old_syms.at(i) = tape.at(i).at(heads.at(i));
    }
    std::set<tuple> delta = tm.get_delta();
    bool is_stop = true;
    tuple trans;
    for (auto it = delta.begin(); it != delta.end(); it ++) {
        if (it->old_state == cur_state && is_equal_syms(old_syms, it->old_syms)) {
            trans = *it;
            is_stop = false;
            break;
        }
    }
    if (is_stop) {
        return false;
    } else {
        cur_state = trans.new_state;
        for (int i = 0; i < N; i ++) {
            if (trans.new_syms.at(i) == '*') continue;
            tape.at(i).at(heads.at(i)) = trans.new_syms.at(i);
        }
        move_heads(trans.dirs);
    }
    return true;
}

void simulator::print_tape(int tape_index) {
    start = 0;
    for (int i = 0; i < tape.at(tape_index).size(); i ++) {
        if (tape.at(tape_index).at(i) == '_') {
            start ++;
        } else {
            break;
        }
    }
    end = tape.at(tape_index).size() - 1;
    for (int i = tape.at(tape_index).size() - 1; i >= 0; i --) {
        if (tape.at(tape_index).at(i) == '_') {
            end --;
        } else {
            break;
        }
    }
    for (int i = start; i <= end; i ++) {
        std::cout<< tape.at(tape_index).at(i);
    }
    std::cout << std::endl;
}

void simulator::print_tape_index(int tape_index, int zero_pos) {
    verbose_index.resize(0);
    start = 0;
    for (int i = 0; i < tape.at(tape_index).size(); i ++) {
        if (tape.at(tape_index).at(i) == '_') {
            start ++;
        } else {
            break;
        }
    }
    end = tape.at(tape_index).size() - 1;
    for (int i = tape.at(tape_index).size() - 1; i >= 0; i --) {
        if (tape.at(tape_index).at(i) == '_') {
            end --;
        } else {
            break;
        }
    }
    int head_pos = heads.at(tape_index);
    if (head_pos < start) start = head_pos;
    if (head_pos > end) end = head_pos;
    int verbose_num = 0;
    if (start < zero_pos && end > zero_pos) {
        for (int i = start; i < zero_pos; i++)
        {
            std::cout << zero_pos - i << " ";
            verbose_index.push_back(verbose_num);
            if ((zero_pos - i) >= 10){
                verbose_num += 3;
            } else {
                verbose_num += 2;
            }
        }
        for (int i = zero_pos; i <= end; i++)
        {
            std::cout << i - zero_pos << " ";
            verbose_index.push_back(verbose_num);
            if ((i - zero_pos) >= 10){
                verbose_num += 3;
            } else {
                verbose_num += 2;
            }
        }
        verbose_index.push_back(verbose_num);
        std::cout << std::endl;
    } else if (zero_pos <= start) {
        for (int i = start; i <= end; i++)
        {
            std::cout << i - zero_pos << " ";
            verbose_index.push_back(verbose_num);
            if ((i - zero_pos) >= 10){
                verbose_num += 3;
            } else {
                verbose_num += 2;
            }
        }
        verbose_index.push_back(verbose_num);
        std::cout << std::endl;
    } else if (zero_pos >= end) {
        for (int i = start; i <= end; i++)
        {
            std::cout << zero_pos - i << " ";
            verbose_index.push_back(verbose_num);
            if ((zero_pos - i) >= 10){
                verbose_num += 3;
            } else {
                verbose_num += 2;
            }
        }
        verbose_index.push_back(verbose_num);
        std::cout << std::endl;
    }
}

void simulator::print_verbose_tape(int tape_index) {
    for (int i = start; i < end; i++)
    {
        std::cout << tape.at(tape_index).at(i);
        for (int j = 0; j < verbose_index.at(i - start + 1) - verbose_index.at(i - start) - 1; j++)
        {
            std::cout << " ";
        }
    }
    std::cout << tape.at(tape_index).at(end);
    std::cout << std::endl;
}

void simulator::print_head(int head_pos) {
    int find_index = head_pos - start;
    int blank_index = verbose_index.at(find_index);
    for (int i = 0; i < blank_index; i++)
    {
        std::cout << " ";
    }
    std::cout << "^" << std::endl;
}

void simulator::print_verbose() {
    std::cout << "Step" << "   " << ": " << steps << std::endl;
    std::cout << "State" << "  " << ": " << cur_state << std::endl;
    int N = tm.get_tape_num();
    for (int i = 0; i < N; i++)
    {
        int zero_standard = zero_positions.at(i);
        std::cout << "Index" << i << " " << ": ";
        print_tape_index(i, zero_standard);
        std::cout << "Tape" << i << "  " << ": ";
        print_verbose_tape(i);
        std::cout << "Head" << i << "  " << ": ";
        int head_pos = heads.at(i);
        print_head(head_pos);
    }
    std::cout << "---------------------------------------------" << std::endl;
}

void simulator::run_turing(bool is_verbose) {
    while(true) {
        if (is_verbose) {
            print_verbose();
        }
        if (!transition()) break;
        steps ++;
    }
    if (is_verbose) {
        std::cout << "Result: ";
    }
    print_tape(0);
    if (is_verbose) {
        std::cout << "==================== END ====================" << std::endl;
    }
}



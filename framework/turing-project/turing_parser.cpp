# include <iostream>
#include <new>
# include <vector>
# include <string>
# include <cstring>
# include <set>
# include <sstream>
# include "turing_parser.hpp"


std::set<std::string> turing_machine::split_line(const std::string& strs, bool is_verbose, int line_count) {
    std::string line = strs;
    int left_br = line.find("{");
    if (left_br == -1) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    line = line.substr(left_br + 1);
    int right_br = line.find("}");
    if (right_br == -1) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    line = line.substr(0, right_br);
    std::set<std::string> res;
    if (line == "") return res;
    char* str = new char[line.size() + 1];
    strcpy(str, line.c_str());
    std::string delim = ",";
    char* d = new char[delim.size() + 1];
    strcpy(d, delim.c_str());
    char* p = strtok(str, d);
    while (p) {
        std::string temp = p;
        judge_Q(temp, is_verbose, line_count);
        res.insert(temp);
        p = strtok(NULL, d);
    }
    delete[]str;
    delete[]d;
    return res;
}

void turing_machine::judge_Q(std::string temp, bool is_verbose, int line_count) {
    for (int i = 0; i < temp.size(); i++)
    {
        char t = temp.at(i);
        if ((t >= 48 && t <= 57) || (t >= 65 && t <= 90) || (t >= 97 && t <= 122) || t == 95 ) {
            continue;
        } else {
            if (is_verbose) {
                std::cerr << "line " << line_count << " error" << std::endl;
                exit(-1);
            } else {
                std::cerr << "syntax error" << std::endl;
                exit(-1);
            }
        }
    }
}

void turing_machine::judge_S(char temp, bool is_verbose, int line_count) {
    if (temp == ' ' || temp == ',' || temp == ';' || temp == '{' || temp == '}' || temp == '*' || temp == '_') {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
}

void turing_machine::judge_G(char temp, bool is_verbose, int line_count) {
    if (temp == ' ' || temp == ',' || temp == ';' || temp == '{' || temp == '}' || temp == '*') {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
}



std::set<char> turing_machine::split_lone_line(const std::string& strs, bool is_verbose, int line_count, bool is_S) {
    std::string line = strs;
    int left_br = line.find("{");
    if (left_br == -1) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    line = line.substr(left_br + 1);
    int right_br = line.find("}");
    if (right_br == -1) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    line = line.substr(0, right_br);
    std::set<char> res;
    if (line == "") return res;
    char* str = new char[line.size() + 1];
    strcpy(str, line.c_str());
    std::string delim = ",";
    char* d = new char[delim.size() + 1];
    strcpy(d, delim.c_str());
    char* p = strtok(str, d);
    while (p) {
        std::string temp = p;
        if (temp.size() != 1) {
            if (is_verbose) {
                std::cerr << "line " << line_count << " error" << std::endl;
                exit(-1);
            } else {
                std::cerr << "syntax error" << std::endl;
                exit(-1);
            }
        }
        char lone_temp = *temp.c_str();
        if (is_S) {
            judge_S(lone_temp, is_verbose, line_count);
        } else {
            judge_G(lone_temp, is_verbose, line_count);
        }
        res.insert(lone_temp);
        p = strtok(NULL, d);
    }
    delete[]str;
    delete[]d;
    return res;
}

std::string turing_machine::preprocess_string(const std::string& line,  bool is_verbose, int line_count) {
    int judgement = line.find(";");
    std::string sub_line = "";
    if (judgement != -1) {
        sub_line = line.substr(0, judgement);
    } else {
        sub_line = line;
    }
    int index = 0;
    if( !sub_line.empty())
    {
        while( (index = sub_line.find(' ',index)) != std::string::npos)
        {
            sub_line.erase(index,1);
        }
    }
    return sub_line;
}

std::string turing_machine::preprocess_delta_string(const std::string& line,  bool is_verbose, int line_count) {
    int judgement = line.find(";");
    if (judgement == -1) return line;
    std::string sub_line = line.substr(0, judgement);
    return sub_line;
}

void turing_machine::fill_Q(std::string &line, bool is_verbose, int line_count) {
    Q = split_line(line, is_verbose, line_count);
}

void turing_machine::fill_S(std::string &line, bool is_verbose, int line_count) {
    S = split_lone_line(line, is_verbose, line_count, true);
}

void turing_machine::fill_G(std::string &line, bool is_verbose, int line_count) {
    G = split_lone_line(line, is_verbose, line_count, false);
}

void turing_machine::fill_F(std::string &line, bool is_verbose, int line_count) {
    F = split_line(line, is_verbose, line_count);
}

void turing_machine::fill_B(std::string &line, bool is_verbose, int line_count) {
    int equal_sym = line.find("=");
    std::string B_sym = preprocess_string(line, is_verbose, line_count);
    B_sym = line.substr(equal_sym);
    B_sym = B_sym.substr(1);
    //B_sym length??
    B = *B_sym.c_str();
}

void turing_machine::fill_q0(std::string &line, bool is_verbose, int line_count) {
    int equal_sym = line.find("=");
    std::string q0_sym = preprocess_string(line, is_verbose, line_count);
    q0_sym = line.substr(equal_sym);
    q0_sym = q0_sym.substr(1);
    q0 = q0_sym;
}

void turing_machine::fill_N(std::string &line, bool is_verbose, int line_count) {
    int equal_sym = line.find("=");
    std::string N_sym = line.substr(equal_sym);
    N_sym = N_sym.substr(1);
    N = atoi(N_sym.c_str());
}

void turing_machine::fill_delta(std::string &line,  bool is_verbose, int line_count) {
    tuple cur_tuple;
    std::string the_tuple = preprocess_delta_string(line, is_verbose, line_count);
    std::istringstream ss(the_tuple);
    std::string word;
    cur_tuple.index = line_count;
    ss >> word;
    if (word.size() == 0) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    cur_tuple.old_state = word;
    ss >> word;
    if (word.size() == 0) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    for (int i = 0; i < word.size(); i++) {
        //check
        cur_tuple.old_syms.push_back(word[i]);
    }
    ss >> word;
    if (word.size() == 0) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    for (int i = 0; i < word.size(); i++) {
        //check
        cur_tuple.new_syms.push_back(word[i]);
    }
    ss >> word;
    if (word.size() == 0) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    for (int i = 0; i < word.size(); i++) {
        //check
        if (word.at(i) == 'l') {
            cur_tuple.dirs.push_back(dir::LEFT);
        } else if (word.at(i) == 'r') {
            cur_tuple.dirs.push_back(dir::RIGHT);
        } else if (word.at(i) == '*') {
            cur_tuple.dirs.push_back(dir::STAY);
        } else {
            if (is_verbose) {
                std::cerr << "line " << line_count << " error" << std::endl;
                exit(-1);
            } else {
                std::cerr << "syntax error" << std::endl;
                exit(-1);
            }
        }
    }
    ss >> word;
    if (word.size() == 0) {
        if (is_verbose) {
            std::cerr << "line " << line_count << " error" << std::endl;
            exit(-1);
        } else {
            std::cerr << "syntax error" << std::endl;
            exit(-1);
        }
    }
    cur_tuple.new_state = word;
    delta.insert(cur_tuple);
}

#ifndef PARTH_H
#define  PARTH_H

# include <iostream>
#include <new>
# include <vector>
# include <string>
# include <cstring>
# include <set>
# include <unordered_set>


enum dir{
    LEFT,
    RIGHT,
    STAY
};


struct tuple {
    int index;
    std::string old_state;
    std::vector<char> old_syms;
    std::vector<char> new_syms;
    std::vector<dir> dirs;
    std::string new_state;
    tuple() {
        index = 0;
        old_state = "";
        old_syms={};
        new_syms={};
        dirs={};
        new_state = "";
    }
    bool operator< (const tuple &a)const
	{
		return a.index > index;	//由小到大排列
    }
};

class turing_machine {
    private:
        std::set<std::string> Q={};
        std::set<char> S={};
        std::set<char> G={};
        std::string q0;
        std::set<std::string> F={};
        int N;
        char B;
        std::set<tuple> delta{};
    
    public:
        turing_machine()
        :q0(""),
        N(0),
        B('_')
        {};

        std::set<std::string> split_line(const std::string& strs, bool is_verbose, int line_count);

        std::set<char> split_lone_line(const std::string& strs,  bool is_verbose, int line_count, bool is_S); 

        std::string preprocess_string(const std::string& line,  bool is_verbose, int line_count); 

        std::string preprocess_delta_string(const std::string& line,  bool is_verbose, int line_count); 

        void fill_Q(std::string &line,  bool is_verbose, int line_count);

        void fill_S(std::string &line,  bool is_verbose, int line_count);

        void fill_G(std::string &line, bool is_verbose, int line_count);
        
        void fill_F(std::string &line, bool is_verbose, int line_count);

        void fill_B(std::string &line, bool is_verbose, int line_count);

        void fill_q0(std::string &line, bool is_verbose, int line_count); 

        void fill_N(std::string &line, bool is_verbose, int line_count);

        void fill_delta(std::string &line, bool is_verbose, int line_count); 

        int get_tape_num() { return N; };

        std::set<std::string>& get_Q() { return Q; };

        std::set<char>& get_S() { return S; };

        std::set<tuple>& get_delta() { return delta; };

        std::string get_q0() { return q0; };

        void judge_Q(std::string temp, bool is_verbose, int line_count);

        void judge_S(char temp, bool is_verbose, int line_count);

        void judge_G(char temp, bool is_verbose, int line_count);
};

#endif
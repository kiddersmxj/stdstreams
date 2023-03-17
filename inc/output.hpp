#ifndef KOUTPUT
#define KOUTPUT

#include "../lib/std-k/std-k.hpp"
#include "config.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Output {
    public:
        Output(std::string Input);
    private:
        std::string Input;
        std::vector<std::string> All;
        std::vector<std::string> Names;
        std::vector<std::string> Values;
        std::vector<std::string> Status;
};

void ReplaceFirst(std::string& s ,std::string const& ToReplace, std::string const& ReplaceWith);

#endif

#ifndef KOUTPUT
#define KOUTPUT

#include "../lib/std-k.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Output {
    public:
        Output(std::string Input);
        void Parse(std::string Input);
    private:
        std::string Input;
        std::vector<std::string> All;
        std::vector<std::string> Names;
        std::vector<std::string> Values;
        std::vector<std::string> Status;
};

void ParseStatus(std::vector<std::string> &Names, std::vector<std::string> &Values, std::vector<std::string> &Status);
void SeperateNamesValues(std::vector<std::string> &All, std::vector<std::string> &Names, std::vector<std::string> &Values);
std::vector<std::string> SeperateInput(std::string Input);
std::string IdentifyEmptyValues(std::string Input);
void ReplaceFirst(std::string& s ,std::string const& ToReplace, std::string const& ReplaceWith);

#endif
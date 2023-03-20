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
        int GetNoOfInts();
        std::vector<int> GetIntLocations();
        int GetInt();
        int GetIntValue(int Index);
        std::string GetIntName(int Index);
    private:
        std::string Input;
        std::vector<int> IntegerLocations;
        std::vector<std::string> All;
        std::vector<std::string> Names;
        std::vector<std::string> Values;
        std::vector<std::string> Status;
};


std::vector<int> ParseIntegers(std::vector<std::string> Values);
bool IsInteger(std::string str);
void ParseStatus(std::vector<std::string> &Names, std::vector<std::string> &Values, std::vector<std::string> &Status);
void SeperateNamesValues(std::vector<std::string> &All, std::vector<std::string> &Names, std::vector<std::string> &Values);
std::vector<std::string> SeperateInput(std::string Input);
std::string IdentifyEmptyValues(std::string Input);
void ReplaceFirst(std::string& s ,std::string const& ToReplace, std::string const& ReplaceWith);

#endif

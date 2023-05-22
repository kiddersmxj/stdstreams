/* Copyright (c) 2023, Maxamilian Kidd-May */
/* All rights reserved. */

/* This source code is licensed under the MIT license found in the */
/* LICENSE file in the root directory of this source tree. */ 

#ifndef KOUTPUT
#define KOUTPUT

#include "config.hpp"

#include <std-k.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

class Output {
    public:
        Output(std::string Input);
        void Parse(std::string Input);
        std::vector<int> GetIntLocations();
        std::vector<int> GetStrLocations();
        std::string GetValue(int Index);
        std::string GetName(int Index);
        std::vector<std::string> GetStatus();
        void RecordInt(int Int, int Index);
        std::vector<std::vector<int>> GetInts();
        int GetMaxInt(int Index);
        int GetMinInt(int Index);
        int GetAvgInt(int Index);
        std::string GetPreviousInts(int Index, int Num);
        std::string GetPreviousInt(int Index, int Num);
        int GetMaxStatuses();
    private:
        bool IntMatrixCreated = 0;
        std::string Input;
        std::vector<int> MaxInts;
        std::vector<int> MinInts;
        std::vector<int> AvgInts;
        std::vector<std::vector<int>> Ints;
        std::vector<int> IntegerLocations;
        std::vector<std::string> All;
        std::vector<std::string> Names;
        std::vector<std::string> Values;
        std::vector<std::string> Status;
        int MaxStatuses = 0;
        void CreateIntMatrix(int Int);
        void ParseIntegers(std::vector<std::string> Values);
        void ParseStatus(std::vector<std::string> &Names, std::vector<std::string> &Values, std::vector<std::string> &Status);
        void SeperateNamesValues(std::vector<std::string> &All, std::vector<std::string> &Names, std::vector<std::string> &Values);
        std::vector<std::string> SeperateInput(std::string Input);
        std::string IdentifyEmptyValues(std::string Input);
        void ReplaceFirst(std::string &s ,std::string const &ToReplace, std::string const &ReplaceWith);
};


#endif

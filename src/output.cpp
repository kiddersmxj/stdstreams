/* Copyright (c) 2023, Maxamilian Kidd-May */
/* All rights reserved. */

/* This source code is licensed under the MIT license found in the */
/* LICENSE file in the root directory of this source tree. */ 

#include "../inc/output.hpp"

// Constructor parses child input
Output::Output(std::string Input) {
    Parse(Input);
}

void Output::Parse(std::string Input) {
    // Make sure the vectors that dont record are clear from last input
    Names.clear();
    Values.clear();
    Status.clear();
    // Clear locations of ints - probably undeeded
    IntegerLocations.clear();
    // Adds no data mark
    Input = IdentifyEmptyValues(Input);
    // Delims based on comma
    All = SeperateInput(Input);
    // Seperates into respective vectors
    SeperateNamesValues(All, Names, Values);
    // Gets names flagged as status and adds to vector
    ParseStatus(Names, Values, Status);
    // Function chain creating stored int lists
    ParseIntegers(Values);
}

std::string Output::GetValue(int Index) {
    std::string Value = Values[Index];
    return Value;
}

std::string Output::GetName(int Index) {
    std::string Name = Names[Index];
    return Name;
}

std::vector<int> Output::GetIntLocations() {
    return IntegerLocations;
}

std::vector<std::string> Output::GetStatus() {
    return Status;
}

// Records where strings are for display
std::vector<int> Output::GetStrLocations() {
    std::vector<int> StringLocations;
    std::vector<std::string> tmpStringLocations;

    // Builds a framework for correctly sized vector to allow use of at()
    for(int i(0); i<Names.size(); i++)
        tmpStringLocations.push_back(std::to_string(i));

    // Finds elements with integers from vector (as int locations already exists) and adds replacment
    const std::string Replacment = "dgfhgjvhkjljfcghvjhkjlkjfchl";
    for(int i: IntegerLocations)
        k::ReplaceFirst(tmpStringLocations.at(i), std::to_string(i), Replacment);

    // Removes contain earlier replaced replacment
    std::vector<std::string>::iterator i = tmpStringLocations.begin();
    while(i != tmpStringLocations.end()) {
        if(i->find(Replacment, 0) != std::string::npos) {
            i = tmpStringLocations.erase(i);
        } else i++;
    }

    // Copy tmp vector to actual
    for(std::string i: tmpStringLocations)
        StringLocations.push_back((stoi(i)));
    return StringLocations;
}

// Builds framework for multilayer int recording matrix
void Output::CreateIntMatrix(int Int) {
    // Inner vector initialisation
    std::vector<int> V;
    V.push_back(Int);
    // Add inner vector to main to initialise
    Ints.push_back(V);
    
    // Build matrix depending on number of ints
    for(int i=0; i<Ints.size(); i++) {
        MaxInts.push_back(1);
        MinInts.push_back(1);
        AvgInts.push_back(1);
    }
}

// Stores ints in matrix
void Output::RecordInt(int Int, int Index) {
    // Add int to respective indexed row of matrix at the front (for graph)
    Ints[Index].insert(Ints[Index].begin(), Int);

    // If max storage reached the remove oldest value
    if(Ints[Index].size() > MaxValueStorage)
        Ints[Index].pop_back();

    // Get int status bar info
    MaxInts.at(Index) = *max_element(std::begin(Ints[Index]), std::end(Ints[Index]));
    MinInts.at(Index) = *min_element(std::begin(Ints[Index]), std::end(Ints[Index]));
    // TODO check divide by zero error
    AvgInts.at(Index) = k::Average(Ints[Index]);
}

// Creates all int respective vectors
void Output::ParseIntegers(std::vector<std::string> Values) {
    int i = 0;
    int j = 0;
    for(std::string s: Values) {
        if(k::IsInteger(s)) {
            // If an int the add location to locations
            IntegerLocations.push_back(i);
            // If matrix has been created then record if not then create to prevent invlaid size
            if(IntMatrixCreated)
                RecordInt(stoi(s), j);
            else if(!IntMatrixCreated) {
                CreateIntMatrix(stoi(s));
            }
            j++;
        }
        i++;
    }
    // Once called once then record will have been created
    IntMatrixCreated = 1;
}

std::vector<std::vector<int>> Output::GetInts() {
    return Ints;
}

int Output::GetMaxInt(int Index) {
    return MaxInts.at(Index);
}

int Output::GetMinInt(int Index) {
    return MinInts.at(Index);
}

int Output::GetAvgInt(int Index) {
    return AvgInts.at(Index);
}

int Output::GetMaxStatuses() {
    return MaxStatuses;
}

// Gets int from index in matrix num numbers before the current
std::string Output::GetPreviousInt(int Index, int Num) {
    Num++;
    // Check to make sure the number actaully exists
    if(Num < Ints[Index].size()) {
        return std::to_string(Ints[Index].at(Num));
    }
    return "";
}

// Adds status marked names to status values
void Output::ParseStatus(std::vector<std::string> &Names, std::vector<std::string> &Values, std::vector<std::string> &Status) {
    // How many statuses exist
    int NumStatus = 0;
    // Use a copy to properly iterate through as you delete status elements from names and values
    std::vector<std::string> NamesCopy = Names;
    for(std::string stat: NamesCopy) {
        // TODO Functionise to add as many keywords to add to status message as user requires
        if(stat.find(StatusTitle) != std::string::npos || stat.find("status") != std::string::npos || stat.find("Status") != std::string::npos) {
            NumStatus++;
            // Find position of status in values
            int Index = k::VGetIndex(Names, stat);
            // Add the value to statuses and remove elements from names and values as now undeeded
            Status.push_back(Values[Index]);
            Names.erase(Names.begin() + Index);
            Values.erase(Values.begin() + Index);
        }
    }
    // Set max size to properly size box
    if(NumStatus > MaxStatuses)
        MaxStatuses = NumStatus;
}

// Splits output using delim into two vectors that run parralel to eachother
void Output::SeperateNamesValues(std::vector<std::string> &All, std::vector<std::string> &Names, std::vector<std::string> &Values) {
    // Flip to alternate between name and value (should correspond/alternate) to put in correct vector
    bool NameValueFlip = 0;
    const char* EqualsDelim = "=";

    for(std::string t: All) {
        std::stringstream ss(t);
        // Gets line up to equals
        while(std::getline(ss, t, *EqualsDelim)) { 
            // Removes traling newline
            t.erase(std::remove(t.begin(), t.end(), '\n'), t.cend());
            // Adds to respective vector depending on before/after delim
            if(!NameValueFlip)
                Names.push_back(t);
            else if(NameValueFlip)
                Values.push_back(t);
            // Switch flip to alternate to opposite vector as name correseponds to a value
            NameValueFlip = !NameValueFlip;
        }
    }
}

// Seperates lines/variables by comman delim
std::vector<std::string> Output::SeperateInput(std::string Input) {
    // String to use to hold each line to push to vector
    std::string s;
    const char* CommaDelim = ",";
    // Vector to return
    std::vector<std::string> V;

    std::stringstream ss(Input); 
    // Get line to comma delim
    while (std::getline(ss, s, *CommaDelim)) { 
        // Remove whitespace if present at begining of string (usually before name)
        if(s.at(0) == ' ')
            s.erase(0, 1);
        // Add adjusted string holding name=value to return vector
        V.push_back(s); 
    }
    return V;
}

// Gets empty values and fills them with no data mark
std::string Output::IdentifyEmptyValues(std::string Input) {
    const char* EmptyDelim = "=,";

    // Finds blank spots
    while(Input.find(EmptyDelim) != std::string::npos) {
        // Replaces with no data mark in input vector
        k::ReplaceFirst(Input, "=,", "=" + NoDataMarkInternal + ",");
    }

    return Input;
}


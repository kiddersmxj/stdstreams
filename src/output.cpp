#include "../inc/output.hpp"
#include <cstddef>
#include <std-k.hpp>
#include <string>
#include <vector>

Output::Output(std::string Input) {
    /* Input = Input; */
    /* Input = IdentifyEmptyValues(Input); */
    /* All = SeperateInput(Input); */
    /* SeperateNamesValues(All, Names, Values); */
    /* ParseStatus(Names, Values, Status); */
    /* IntegerLocations = ParseIntegers(Values); */
    Parse(Input);
#ifdef OCOUT
    std::cout << "No of ints: " << IntegerLocations.size() << std::endl;

    std::cout << std::endl << "All:" << std::endl;
    k::VPrint(All);
    std::cout << std::endl << "Names:" << std::endl;
    k::VPrint(Names);
    std::cout << std::endl << "Values:" << std::endl;
    k::VPrint(Values);
    std::cout << std::endl << "Status:" << std::endl;
    k::VPrint(Status);
#endif
}

void Output::Parse(std::string Input) {
    Names.clear();
    Values.clear();
    Status.clear();
    IntegerLocations.clear();
    Input = IdentifyEmptyValues(Input);
    All = SeperateInput(Input);
    SeperateNamesValues(All, Names, Values);
    ParseStatus(Names, Values, Status);
    ParseIntegers(Values);
#ifdef OCOUT
    std::cout << "Parsing complete" << std::endl;
    std::cout << "Out: " << std::endl;
    k::VPrint(Names);
    k::VPrint(Values);
    k::VPrint(Status);
    for(int i: IntegerLocations)
        std::cout << i << std::endl;
#endif
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

std::vector<int> Output::GetStrLocations() {
    std::vector<int> StringLocations;
    std::vector<std::string> tmpStringLocations;
    for(int i(0); i<Names.size(); i++)
        tmpStringLocations.push_back(std::to_string(i));
    for(int i: IntegerLocations) {
        const std::string Replacment = "NAna";
        const std::string I = std::to_string(i);
        ReplaceFirst(tmpStringLocations[i], I, Replacment);
    }
    std::vector<std::string>::iterator i = tmpStringLocations.begin();
    while(i != tmpStringLocations.end()) {
        if(i->find("NAna", 0) != std::string::npos) {
            i = tmpStringLocations.erase(i);
        } else {
            ++i;
        }
    }
    for(std::string i: tmpStringLocations) {
        StringLocations.push_back((stoi(i)));
    }
    return StringLocations;
}

std::vector<std::string> Output::GetStatus() {
    return Status;
}

void Output::CreateIntMatrix(int Int) {
    std::vector<int> v;
    v.push_back(Int);
    Ints.push_back(v);
    
    int in = 0;
    for(std::vector<int> v: Ints) {
#ifdef OCOUT
        std::cout << "Creation start of v " << in << std::endl;
#endif
        for(int i: v)
#ifdef OCOUT
            std::cout << "i: " << i << std::endl;
#endif
        in++;
    }
#ifdef OCOUT
    std::cout << "int size: " << Ints.size() << " Iloco size: " << IntegerLocations.size() << std::endl;
#endif
    for(int i=0; i<Ints.size(); i++)
        MaxInts.push_back(0);
}

void Output::RecordInt(int Int, int Index) {
#ifdef OCOUT
    std::cout << "Recorded Int: " << Int << " Index: " << Index << std::endl;
#endif
    Ints[Index].insert(Ints[Index].begin(), Int);
    if(Ints[Index].size() > 400 )
        Ints[Index].pop_back();
#ifdef ECOUT
    for(int i: Ints[Index])
        std::cout << "Vector with ints in: " << i << std::endl;
    std::cout << "max (" << Index << "): " << *max_element(std::begin(Ints[Index]), std::end(Ints[Index])) << std::endl;
#endif
    MaxInts.at(Index) = *max_element(std::begin(Ints[Index]), std::end(Ints[Index]));
}

void Output::ParseIntegers(std::vector<std::string> Values) {
    int i = 0;
    int j = 0;
    for(std::string s: Values) {
        if(IsInteger(s)) {
            IntegerLocations.push_back(i);
            if(IntRecordCreated)
                RecordInt(stoi(s), j);
            else if(!IntRecordCreated) {
                CreateIntMatrix(stoi(s));
            }
            j++;
        }
        i++;
    }
    IntRecordCreated = 1;
#ifdef ECOUT
    int in = 0;
    for(std::vector<int> v: Ints) {
        std::cout << "start of v " << in << std::endl;
        for(int i: v)
            std::cout << "i2: " << i << std::endl;
        in++;
    }
#endif
}

std::vector<std::vector<int>> Output::GetInts() {
    return Ints;
}

int Output::GetMaxInt(int Index) {
    return MaxInts.at(Index);
}

bool IsInteger(std::string str) {
    bool rtn = !str.empty() && str.find_first_not_of("0123456789-.") == std::string::npos;
    return rtn;
}

void ParseStatus(std::vector<std::string> &Names, std::vector<std::string> &Values, std::vector<std::string> &Status) {
    // Use a copy to properly terate through as you delete status elements from names and values
    std::vector<std::string> NamesCopy = Names;
    for(std::string stat: NamesCopy) {
        // TODO Functionise to add as many keywords to add to status message as user requires
        if(stat.find("status") != std::string::npos || stat.find("Status") != std::string::npos) {
            int Index = k::VGetIndex(Names, stat);
            Status.push_back(Values[Index]);
            Names.erase(Names.begin() + Index);
            Values.erase(Values.begin() + Index);
        }
    }
}

void SeperateNamesValues(std::vector<std::string> &All, std::vector<std::string> &Names, std::vector<std::string> &Values) {
    int NameValueFlip = 0;
    auto EqualsDelim = "=";
    for(std::string t: All) {
        std::string tt;
        std::stringstream sst(t);
        while (std::getline(sst, t, *EqualsDelim)) { 
            t.erase(std::remove(t.begin(), t.end(), '\n'), t.cend());
            if(!NameValueFlip)
                Names.push_back(t);
            else if(NameValueFlip)
                Values.push_back(t);
            NameValueFlip = ! NameValueFlip;
        }
    }
}

std::vector<std::string> SeperateInput(std::string Input) {
    bool Quote = 0;
    std::string tmp;
    std::string s;
    std::vector<std::string> V;
    auto CommaDelim = ",";
    std::stringstream ss(Input); 
    while (std::getline(ss, s, *CommaDelim)) { 
        if(s.at(0) == ' ') {
            s.erase(0, 1);
        }
        V.push_back(s); 
    }
    return V;
}

std::string IdentifyEmptyValues(std::string Input) {
    auto EmptyDelim = "=,";
    std::string NoDataMarkInternal = "NAna";
    while(Input.find(EmptyDelim) != std::string::npos) {
        ReplaceFirst(Input, "=,", "=" + NoDataMarkInternal + ",");
    }
    return Input;
}

void ReplaceFirst(std::string &s ,std::string const &ToReplace, std::string const &ReplaceWith) {
    std::size_t pos = s.find(ToReplace);
    if (pos == std::string::npos) return;
    s.replace(pos, ToReplace.length(), ReplaceWith);
}

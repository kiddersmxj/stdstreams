#include "../inc/output.hpp"
#include <cstddef>
#include <string>
#include <vector>

Output::Output(std::string Input) {
    Input = Input;
 
    auto QuoteDelim = R"(")";
    auto SpaceDelim = " ";

    Input = IdentifyEmptyValues(Input);
    All = SeperateInput(Input);
    SeperateNamesValues(All, Names, Values);
    ParseStatus(Names, Values, Status);

#ifdef OCCOUT
    std::cout << std::endl << "All:" << std::endl;
    VPrint(All);
    std::cout << std::endl << "Names:" << std::endl;
    VPrint(Names);
    std::cout << std::endl << "Values:" << std::endl;
    VPrint(Values);
    std::cout << std::endl << "Status:" << std::endl;
    VPrint(Status);
#endif
}

void Output::Parse(std::string Input) {
    Names.clear();
    Values.clear();
    Status.clear();
    Input = IdentifyEmptyValues(Input);
    All = SeperateInput(Input);
    SeperateNamesValues(All, Names, Values);
    ParseStatus(Names, Values, Status);
    IntegerLocations = ParseIntegers(Values);
#ifdef OCOUT
    std::cout << "Out: " << std::endl;
    VPrint(Names);
    VPrint(Values);
    VPrint(Status);
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

std::vector<int> ParseIntegers(std::vector<std::string> Values) {
    std::vector<int> IntegersLocations;
    int i = 0;
    for(std::string s: Values) {
        if(IsInteger(s)) {
            IntegersLocations.push_back(i);
        }
        i++;
    }
    return IntegersLocations;
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
            int Index = VGetIndex(Names, stat);
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

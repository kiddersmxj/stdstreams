#include "../inc/output.hpp"
#include <vector>

Output::Output(std::string Input) {
    Input = Input;
 
    auto QuoteDelim = R"(")";
    auto SpaceDelim = " ";

    Input = IdentifyEmptyValues(Input);
    All = SeperateInput(Input);
    SeperateNamesValues(All, Names, Values);
    ParseStatus(Names, Values, Status);

    std::cout << std::endl << "All:" << std::endl;
    VPrint(All);
    std::cout << std::endl << "Names:" << std::endl;
    VPrint(Names);
    std::cout << std::endl << "Values:" << std::endl;
    VPrint(Values);
    std::cout << std::endl << "Status:" << std::endl;
    VPrint(Status);
}

void Output::Parse(std::string Input) {
    Input = IdentifyEmptyValues(Input);
    All = SeperateInput(Input);
    SeperateNamesValues(All, Names, Values);
    ParseStatus(Names, Values, Status);
}

void ParseStatus(std::vector<std::string> &Names, std::vector<std::string> &Values, std::vector<std::string> &Status) {
    // Use a copy to properly terate through as you delete status elements from names and values
    std::vector<std::string> NamesCopy = Names;
    for(std::string stat: NamesCopy) {
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

void ReplaceFirst(std::string& s ,std::string const& ToReplace, std::string const& ReplaceWith) {
    std::size_t pos = s.find(ToReplace);
    if (pos == std::string::npos) return;
    s.replace(pos, ToReplace.length(), ReplaceWith);
}

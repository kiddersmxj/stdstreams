#include "../inc/output.hpp"

Output::Output(std::string Input) {
    Input = Input;
 
    auto QuoteDelim = R"(")";
    auto SpaceDelim = " ";
    auto EqualsDelim = "=";

    Input = IdentifyEmptyValues(Input);
    All = SeperateInput(Input);

    int NameValueFlip = 0;
    for(std::string t: All) {
        std::stringstream sst(t);
        std::string tt;
        while (std::getline(sst, t, *EqualsDelim)) { 
            if(!NameValueFlip)
                Names.push_back(t);
            else if(NameValueFlip)
                Values.push_back(t);
            NameValueFlip = ! NameValueFlip;
        }
    }

    for(std::string stat: Names) {
        if(stat.find("status") != std::string::npos || stat.find("Status") != std::string::npos) {
            Status.push_back(Values[VGetIndex(Names, stat)]);
        }
    }
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

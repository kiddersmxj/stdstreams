#include "../inc/output.hpp"
#include <cstddef>
#include <cstdlib>

Output::Output(std::string Input) {
    Input = Input;
 
    auto QuoteDelim = R"(")";
    auto SpaceDelim = " ";
    auto CommaDelim = ",";
    auto EqualsDelim = "=";
    auto EmptyDelim = "=,";

    while(Input.find(EmptyDelim) != std::string::npos) {
        ReplaceFirst(Input, "=,", "=" + NoDataMark + ",");
    }

    bool Quote = 0;
    std::string tmp;
    std::string s;
    std::stringstream ss(Input); 
    while (std::getline(ss, s, *CommaDelim)) { 
        if(s.at(0) == ' ') {
            s.erase(0, 1);
        }
        All.push_back(s); 
    }

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
    VPrint(Status);
}

void ReplaceFirst(std::string& s ,std::string const& ToReplace, std::string const& ReplaceWith) {
    std::size_t pos = s.find(ToReplace);
    if (pos == std::string::npos) return;
    s.replace(pos, ToReplace.length(), ReplaceWith);
}

#ifndef KCONFIG
#define KCONFIG
#include <iostream>

const std::string NoDataMark = "NA";
const std::string UsageNotes = R"(
usage: stdstreams [--options] [program]
make sure to give the full path of the program

options:
    -v / --version      Print version and exit successfully

errors may occur when the user running the command does not have 
access to the stdout of the program run. please check this is not 
the case.
)";

#endif

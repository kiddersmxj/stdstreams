#ifndef KCONFIG
#define KCONFIG
#include <iostream>

const std::string ParentName = "stdstreams";
const std::string Version = "0.0.0";
const std::string NoDataMark = "NA";
const std::string UsageNotes = R"(
usage: stdstreams [ -o/--options=value ] [ -p/--program=value ]
make sure to give the full path of the program

options:
    -h / --help         show help and usage notes
    -v / --version      print version and exit
    -p / --program      program to parse stdout

errors may occur when the user running the command does not have 
access to the stdout of the program run. please check this is not 
the case.
)";

#endif

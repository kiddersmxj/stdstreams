#ifndef Kstd
#define Kstd

#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>
#include <array>
#include <algorithm>
#include <filesystem>

void BreakPoint();
std::string ExecCmd(const std::string cmd, const int Output, int ExitStatus);
void WriteFileLines(std::vector<std::string> Lines, std::string File);
std::vector<std::string> ReadFileLines(std::string File);
void VPrint(std::vector<std::string> Input);
int PollClock(const std::string Dir);
void Touch(std::string File);
void Data(std::string Text, std::string File);
std::string StripTrailingNL(std::string Input);
void SplitString(std::string &str, char delim, std::vector<std::string> &out);
int VGetIndex(std::vector<std::string> v, std::string K);

#endif

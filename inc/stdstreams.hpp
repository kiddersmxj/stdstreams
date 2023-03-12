#ifndef KSTDSTREAMS
#define KSTDSTREAMS

#include "../lib/std-k/std-k.hpp"
#include <iostream>
#include <stdio.h>

FILE *LaunchChild(const char* Program);
std::string GetOutput(FILE* fp);

#endif

#ifndef KSTDSTREAMS
#define KSTDSTREAMS

#include <std-k.hpp>
#include "child.hpp"
#include "output.hpp"
#include "config.hpp"
#include "display.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <thread>

void ExitError();
void ExitError(const std::string Message);
void ExitErrorUsage();
void ExitErrorUsage(const char* Message);
const char*  EvalOptions(int argc, char** argv);
void PrintVersion();

#endif

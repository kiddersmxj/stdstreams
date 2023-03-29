#ifndef KSTDSTREAMS
#define KSTDSTREAMS

#include "../lib/std-k/std-k.hpp"
#include "child.hpp"
#include "output.hpp"
#include "config.hpp"
#include "display.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>

void ExitError();
void ExitError(const std::string Message);
void ExitErrorUsage();
void ExitErrorUsage(const char* Message);

#endif

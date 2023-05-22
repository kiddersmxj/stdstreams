/* Copyright (c) 2023, Maxamilian Kidd-May */
/* All rights reserved. */

/* This source code is licensed under the MIT license found in the */
/* LICENSE file in the root directory of this source tree. */ 

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

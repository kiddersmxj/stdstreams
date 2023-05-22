/* Copyright (c) 2023, Maxamilian Kidd-May */
/* All rights reserved. */

/* This source code is licensed under the MIT license found in the */
/* LICENSE file in the root directory of this source tree. */ 

#ifndef KCHILD
#define KCHILD
#include <iostream>
#include <stdio.h>
#include <std-k.hpp>

#define PATH_MAX 1000

class Child {
    public:
        Child(const char* Program);
        std::string Read();
        void Close();
        bool QuestionExit();
    private:
        bool Exit = 0;
        char path[PATH_MAX];
        FILE *child;
};
#endif

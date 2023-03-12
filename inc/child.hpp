#include <iostream>
#include <stdio.h>
#include "../lib/std-k/std-k.hpp"

#define PATH_MAX 1000

class Child {
    public:
        Child(const char* Program);
        std::string Read();
        void Close();
    private:
        char path[PATH_MAX];
        FILE *fp;
};

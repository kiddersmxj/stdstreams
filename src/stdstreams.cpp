#include "../inc/stdstreams.hpp"
#include <cstdio>
#include <cstdlib>

#define PATH_MAX 1000
extern int errno;

int main(int argc, char** argv) {
    if(argv[1] == NULL) {
        errno = EXIT_FAILURE;
        ExitErrorUsage("please pass program to parse");
    }

    const char* Program(argv[1]);

    Display Display;

    Child Child(Program);
    Output Output(Child.Read());

    while(!Child.QuestionExit()) {
        Output.Parse(Child.Read());
        Display.Create(Output);
#ifndef NODISPLAY
        Display.Print();
#endif
    }

    Child.Close();

    return 0;
}

void ExitErrorUsage(){
    std::cout << UsageNotes;
    exit(errno);
}

void ExitErrorUsage(const char* Message) {
    perror(Message);
    ExitErrorUsage();
}

#include "../inc/stdstreams.hpp"

#define PATH_MAX 1000

int main(int argc, char** argv) {
    if(argv[1] == NULL) {
        std::cout << "Please pass program to parse" << std::endl;
        return 1;
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


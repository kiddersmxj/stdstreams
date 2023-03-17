#include "../inc/stdstreams.hpp"

#define PATH_MAX 1000

int main(int argc, char** argv) {
    if(argv[1] == NULL) {
        std::cout << "Please pass program to parse" << std::endl;
        return 1;
    }

    const char* Program(argv[1]);
    bool Exit = 0;

    /* FILE *fp; */
    /* fp = LaunchChild(Program); */
    Child Child(Program);
    Output Output(Child.Read());

    while(!Exit) {
        if(Child.Read() == "EXIT")
            Exit = 1;
    }

    Child.Close();

    return 0;
}


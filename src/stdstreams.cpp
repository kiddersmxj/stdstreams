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

    while(!Exit) {
        /* if(GetOutput(fp) == "EXIT") */
        if(Child.Read() == "EXIT")
            Exit = 1;
    }

    Child.Close();

    return 0;
}

FILE* LaunchChild(const char* Program) {
    FILE *fp;

    std::cout << "Running... " << Program << std::endl;

    fp = popen(Program, "r");
    if (fp == NULL) {
        /* Handle error */;
        std::cout << "popen error" << std::endl;
    }
    return fp;
}

std::string GetOutput(FILE* fp) {
    char path[PATH_MAX];
    if(fgets(path, PATH_MAX, fp) != NULL) {
        printf("\033[0;35m");
        printf("%s", path);
        printf("\033[0m");

        BreakPoint();

        return path;
    } else 
        return "EXIT";
}


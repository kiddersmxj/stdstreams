#include "../inc/child.hpp"

Child::Child(const char* Program) {
    std::cout << "Launching child process... " << Program << std::endl;

    fp = popen(Program, "r");
    if (fp == NULL) {
        /* Handle error */;
        std::cout << "popen error" << std::endl;
    }
}

std::string Child::Read() {
    if(fgets(path, PATH_MAX, fp) != NULL) {
        printf("\033[0;35m");
        printf("%s", path);
        printf("\033[0m");

        BreakPoint();

        return path;
    } else 
        return "EXIT";
}

void Child::Close() {
    int status = pclose(fp);
    if (status == -1) {
        /* Error reported by pclose() */
        printf("Error, reported");
    } else {
        /* Use macros described under wait() to inspect `status' in order
         to determine success/failure of command executed by popen() */
        printf("Done running");
    }
}

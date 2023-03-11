#include "../inc/stdstreams.hpp"
#include <stdio.h>

#define PATH_MAX 1000

int main(int argc, char** argv) {
    if(argv[1] == NULL) {
        std::cout << "Please pass program to parse" << std::endl;
        return 1;
    }
    const char* Program(argv[1]);
    std::cout << "Running... " << Program << std::endl;

    FILE *fp;
    int status;
    char path[PATH_MAX];


    fp = popen(Program, "r");
    if (fp == NULL)
    /* Handle error */;


    while (fgets(path, PATH_MAX, fp) != NULL)
        printf("%s", path);


    status = pclose(fp);
    if (status == -1) {
        /* Error reported by pclose() */
        printf("Error, reported");
    } else {
        /* Use macros described under wait() to inspect `status' in order
         to determine success/failure of command executed by popen() */
        printf("Done running");
    }

    return 0;
}

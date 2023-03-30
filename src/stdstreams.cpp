#include "../inc/stdstreams.hpp"
#include <cstdio>
#include <cstdlib>
#include <getopt.h>

#define PATH_MAX 1000
extern int errno;

int main(int argc, char** argv) {
    int HelpFlag = 0;
    int ProgramFlag = 0;
    int VersionFlag = 0;
    int opt;

    struct option Opts[] = {
        { "help", no_argument, &HelpFlag, 1 },
        { "version", no_argument, &VersionFlag, 1 },
        { "program", required_argument, &ProgramFlag, 1 },
        { 0 }
    };

    /* infinite loop, to be broken when we are done parsing options */
    while (1) {
        opt = getopt_long(argc, argv, "hvp:", Opts, 0);

        /* a return value of -1 indicates that there are no more options */
        if (opt == -1) {
            if(HelpFlag && VersionFlag && ProgramFlag)
                ExitErrorUsage();
            break;
        }
        switch (opt) {
        case 'h':
            HelpFlag = 1;
            break;
        case 'p':
            ProgramFlag = 1;
            break;
        case 'v':
            VersionFlag = 1;
            break;
        case '?':
            /* a return value of '?' indicates that an option was malformed.
             * this could mean that an unrecognized option was given, or that an
             * option which requires an argument did not include an argument.
             */
            ExitErrorUsage();
        default:
            break;
        }
    }
    if(HelpFlag) {
        errno = EXIT_SUCCESS;
        ExitErrorUsage();
    }
    if(VersionFlag) {
        errno = EXIT_SUCCESS;
        PrintVersion();
    }
    if(!ProgramFlag) {
        errno = EXIT_FAILURE;
        ExitErrorUsage("please pass program to parse");
    }
    if(argv[1] == NULL) {
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

void PrintVersion() {
    std::cout << ParentName << ": version " << Version << std::endl;
    exit(EXIT_SUCCESS);
}

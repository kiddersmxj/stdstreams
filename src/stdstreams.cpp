/* Copyright (c) 2023, Maxamilian Kidd-May */
/* All rights reserved. */

/* This source code is licensed under the MIT license found in the */
/* LICENSE file in the root directory of this source tree. */ 

#include "../inc/stdstreams.hpp"
#include <getopt.h>

#define PATH_MAX 1000
extern int errno;

int main(int argc, char** argv) {
    // Evaluate options and chec flags, return child if passed
    const char* Program = EvalOptions(argc, argv);

    // Build screen
    Display Display;

    // Start child
    Child Child(Program);
    // Setup and build output vectors using intial stdout read
    Output Output(Child.Read());

    // While stdout exists
    /* while(!Child.QuestionExit()) { */
    /*     // Create and print a display of the output */
        Display.Create(Output, Child);
    /*     // Parse new output from stdout read */
    /*     Output.Parse(Child.Read()); */
/* #ifdef GDB */
    /*     k::BreakPoint(); */
/* #else */
    /*     // Used to hold program from overruning while loop */
    /*     std::this_thread::sleep_for(std::chrono::milliseconds(ProgramLatency)); */
/* #endif */
    /* } */

    // If while exists then stdout has stopped so close child
    Child.Close();

    return 0;
}

// Exit with error and print usage
void ExitErrorUsage(){
    std::cout << UsageNotes;
    exit(errno);
}

// Exit with error and print usage and message
void ExitErrorUsage(const char* Message) {
    perror(Message);
    ExitErrorUsage();
}

// Print version -v/--version and exist successfully
void PrintVersion() {
    std::cout << ParentName << ": version " << Version << std::endl;
    exit(EXIT_SUCCESS);
}

// Get passed args
const char* EvalOptions(int argc, char** argv) {
    // Flag and arg value initalisation
    const char* Program;
    int HelpFlag = 0;
    int ProgramFlag = 0;
    int VersionFlag = 0;
    int opt;

    // Get opt option defenitions
    struct option Opts[] = {
        { "help", no_argument, &HelpFlag, 1 },
        { "version", no_argument, &VersionFlag, 1 },
        { "program", required_argument, NULL, 'p' },
        { 0 }
    };

    // Infinite loop, to be broken when we are done parsing options
    while (1) {
        opt = getopt_long(argc, argv, "hvp:", Opts, 0);

        // A return value of -1 indicates that there are no more options
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
            Program = optarg;
            break;
        case 'v':
            VersionFlag = 1;
            break;
        case '?':
            /* A return value of '?' indicates that an option was malformed.
             * this could mean that an unrecognized option was given, or that an
             * option which requires an argument did not include an argument.
             */
            ExitErrorUsage();
        default:
            break;
        }
    }
    // Act on flags
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

    // If no flags has previously returned function then return program
    return Program;
}

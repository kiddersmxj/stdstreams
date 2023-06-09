/* Copyright (c) 2023, Maxamilian Kidd-May */
/* All rights reserved. */

/* This source code is licensed under the MIT license found in the */
/* LICENSE file in the root directory of this source tree. */ 

#include "../inc/child.hpp"
#include <std-k.hpp>

// Constructor to launch child
Child::Child(const char* Program) {
    // Create file stream from launching child
    child = popen(Program, "r");
    if (child == NULL) {
        // Handle error
        std::cout << "popen error" << std::endl;
    }
}

// Read child stdout
std::string Child::Read() {
    // If stdout exists read and return
    if(fgets(path, PATH_MAX, child) != NULL) {
        /* std::vector<std::string> p(1); */
        /* p.push_back(path); */
        /* k::WriteFileLines(p, "Output"); */
        return path;
    } else  {
        // If program close or other error then set exit code
        Exit = 1;
        return "EXIT";
    }
}

// Checks if program stdout has terminated
bool Child::QuestionExit() {
    return Exit;
}

// Close the program
void Child::Close() {
    // Close child
    int status = pclose(child);
    // pclose error handling
    if (status == -1)
        // Error reported by pclose()
        printf("Error, reported");
    else
        printf("Done running");
}

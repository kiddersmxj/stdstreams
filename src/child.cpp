#include "../inc/child.hpp"

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

#ifndef KCONFIG
#define KCONFIG
#include <ftxui/screen/color.hpp> // for Color
#include <ftxui/dom/elements.hpp>  // for text, graph, operator|, separator, color, Element, vbox, flex, inverted, operator|=, Fit, hbox, size, border, GREATER_THAN, HEIGHT, Decorator

const std::string ParentName = "stdstreams";
const std::string Version = "0.0.0";
const std::string UsageNotes = R"(
usage: stdstreams [ -o/--options=value ] [ -p/--program=value ]
Make sure to give the full path of the program

options:
    -h / --help         show help and usage notes
    -v / --version      print version and exit
    -p / --program      program to parse stdout

Program can be utilised to parse any program that can or does 
write to stdout. 

Format specified as such:
Mode=Neutral, Speed=41, Potentiometer Position=-29, Status=Throttle
but no drive selected\n,

The use of \n at the end of each line or equivilent endl character
is vital to sucsessful execution. The use of quotes around values 
are not required. Program used the "," comma to delimit its values.
Keeping the order of variables is also nessecary as program uses
indicies to refernece values rather than names.

Errors may occur when the user running the command does not have 
access to the stdout of the program run. Please check this is not 
the case.
)";

// Display
// Colours
const ftxui::Color GreyColours[4] = { ftxui::Color::Default, ftxui::Color::Grey70, ftxui::Color::Grey42, ftxui::Color::Grey23 };
const ftxui::Decorator StrStyle = ftxui::color(ftxui::Color::Red);
const ftxui::Decorator IntStyle = ftxui::color(ftxui::Color::Cyan);
const ftxui::Decorator StatStyle = ftxui::color(ftxui::Color::Green);
const ftxui::Decorator TextStyle = ftxui::color(ftxui::Color::Default);
// Titles
const std::string StatusTitle = "Status";
// Ints
const std::string MinTitle = "min: ";
const std::string MaxTitle = "max: ";
const std::string AvgTitle = "avg: ";
// How many values are cascaded through (must add respective amount to GreyColours[])
const int NumOldValuesShown = 4;

// Output
const std::string NoDataMarkInternal = "NA";
const int MaxValueStorage = 400;

#endif

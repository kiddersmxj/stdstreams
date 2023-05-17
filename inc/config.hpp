#ifndef KCONFIG
#define KCONFIG
#include <cstdint>
#include <iostream>
#include <vector>
#include <ftxui/screen/color.hpp> // for Color
#include <ftxui/dom/elements.hpp>  // for text, graph, operator|, separator, color, Element, vbox, flex, inverted, operator|=, Fit, hbox, size, border, GREATER_THAN, HEIGHT, Decorator

const std::string ParentName = "stdstreams";
const std::string Version = "0.0.0";
const std::string NoDataMarkInternal = "NA";
const std::string UsageNotes = R"(
usage: stdstreams [ -o/--options=value ] [ -p/--program=value ]
make sure to give the full path of the program

options:
    -h / --help         show help and usage notes
    -v / --version      print version and exit
    -p / --program      program to parse stdout

errors may occur when the user running the command does not have 
access to the stdout of the program run. please check this is not 
the case.
)";

// Display
const ftxui::Color GreyColours[4] = { ftxui::Color::Default, ftxui::Color::Grey70, ftxui::Color::Grey42, ftxui::Color::Grey23 };
const ftxui::Decorator StrStyle = ftxui::color(ftxui::Color::Red);
const ftxui::Decorator IntStyle = ftxui::color(ftxui::Color::Cyan);
const ftxui::Decorator StatStyle = ftxui::color(ftxui::Color::Green);
const ftxui::Decorator TextStyle = ftxui::color(ftxui::Color::Default);

#endif

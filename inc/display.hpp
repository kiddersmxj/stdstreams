#ifndef KDISPLAY
#define KDISPLAY

#include <iostream>
#include <chrono>
#include <type_traits>
#include <string>  // for operator+, to_string
#include <vector>  // for vector, __alloc_traits<>::value_type
#include <iostream>
#include <ostream>
#include <vector>

#include <ftxui/component/captured_mouse.hpp>  // for ftxui
#include <ftxui/component/component.hpp>  // for Menu, Renderer, Horizontal, Vertical
#include <ftxui/component/component_base.hpp>  // for ComponentBase
#include <ftxui/dom/elements.hpp>  // for text, graph, operator|, separator, color, Element, vbox, flex, inverted, operator|=, Fit, hbox, size, border, GREATER_THAN, HEIGHT
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <ftxui/screen/string.hpp>
#include <ftxui/dom/node.hpp>  // for Render
#include <ftxui/screen/color.hpp>  // for Color, Color::BlueLight, Color::RedLight, Color::YellowLight, ftxui

#include "config.hpp"
#include "output.hpp"

using namespace ftxui;

class Display {
    public:
        void Close();
        void Print();
        void Create(Output Output);
        std::string ResetPosition;
    private:
        Element Screen;
};

std::vector<Element> GetStatElement(Output Output);
Element GetStrElement(Output Output, int Index);
Element GetIntElement(Output Output, int Index);
std::vector<ftxui::Element> GetSectors();

#endif

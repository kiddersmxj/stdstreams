#ifndef KDISPLAY
#define KDISPLAY

#include <iostream>
#include <chrono>
#include <type_traits>
#include <string>  // for operator+, to_string
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "../lib/component/captured_mouse.hpp"  // for ftxui
#include "../lib/component/component.hpp"  // for Menu, Renderer, Horizontal, Vertical
#include "../lib/component/component_base.hpp"  // for ComponentBase
#include "../lib/dom/elements.hpp"  // for text, graph, operator|, separator, color, Element, vbox, flex, inverted, operator|=, Fit, hbox, size, border, GREATER_THAN, HEIGHT
#include "../lib/screen/screen.hpp"  // for Full, Screen
#include "../lib/dom/node.hpp"  // for Render
#include "../lib/screen/color.hpp"  // for Color, Color::BlueLight, Color::RedLight, Color::YellowLight, ftxui

#include "output.hpp"

class Display {
    public:
        void Close();
        void Print();
        void Create(Output Output);
        std::string ResetPosition;
    private:
        ftxui::Element Screen;
};

ftxui::Element GetStrElement(Output Output, int Index);
ftxui::Element GetIntElement(Output Output, int Index);
std::vector<ftxui::Element> GetSectors();

#endif

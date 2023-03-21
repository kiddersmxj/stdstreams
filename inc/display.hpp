#ifndef KDISPLAY
#define KDISPLAY

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
/* #include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive */
#include "ftxui/dom/elements.hpp"  // for text, Element, operator|, window, flex, vbox
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
 
#include <iostream>
#include <chrono>
#include <type_traits>
#include <string>  // for operator+, to_string
#include <vector>  // for vector, __alloc_traits<>::value_type

#include <ftxui/dom/elements.hpp>  // for graph, operator|, separator, color, Element, vbox, flex, inverted, operator|=, Fit, hbox, size, border, GREATER_THAN, HEIGHT
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include "ftxui/dom/node.hpp"  // for Render
#include "ftxui/screen/color.hpp"  // for Color, Color::BlueLight, Color::RedLight, Color::YellowLight, ftxui

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

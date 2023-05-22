/* Copyright (c) 2023, Maxamilian Kidd-May */
/* All rights reserved. */

/* This source code is licensed under the MIT license found in the */
/* LICENSE file in the root directory of this source tree. */ 

#ifndef KDISPLAY
#define KDISPLAY

#include <iostream>
#include <vector>
#include <string>

#include <ftxui/component/captured_mouse.hpp>  // for ftxui
#include <ftxui/component/component.hpp>  // for Menu, Renderer, Horizontal, Vertical
#include <ftxui/component/component_base.hpp>  // for ComponentBase
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <ftxui/screen/string.hpp>
#include <ftxui/screen/color.hpp>  // for Color, Color::BlueLight, Color::RedLight, Color::YellowLight, ftxui
#include <ftxui/dom/node.hpp>  // for Render
#include <ftxui/dom/elements.hpp>  // for text, graph, operator|, separator, color, Element, vbox, flex, inverted, operator|=, Fit, hbox, size, border, GREATER_THAN, HEIGHT

#include "config.hpp"
#include "output.hpp"

using namespace ftxui;

class Display {
    public:
        void Create(Output Output);
        std::string ResetPosition;
    private:
        std::string Data = "N/A";
        Element Screen;
        int StrHeight = 0;
        int StrWidth = 0;
        Element GetStrElement(Output Output, int Index);
        std::vector<Element> GetStatElement(Output Output);
};


#endif

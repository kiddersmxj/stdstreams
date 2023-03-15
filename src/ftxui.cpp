#include <thread>
#include <chrono>                  // for operator""s, chrono_literals
#include <cmath>                   // for sin
#include <ftxui/dom/elements.hpp>  // for graph, operator|, separator, color, Element, vbox, flex, inverted, operator|=, Fit, hbox, size, border, GREATER_THAN, HEIGHT
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include <functional>               // for ref, reference_wrapper
#include <iostream>                 // for cout, ostream
#include <memory>                   // for shared_ptr
#include <string>                   // for operator<<, string
#include <thread>                   // for sleep_for
#include <vector>                   // for vector

#include "ftxui/dom/node.hpp"  // for Render
#include "ftxui/screen/color.hpp"  // for Color, Color::BlueLight, Color::RedLight, Color::YellowLight, ftxui
#include "../inc/ftxui.hpp"

using namespace ftxui;

std::string Maya(int i) {
    if(i)
        return "miss maya";
    else 
        return "maya";
}

std::chrono::system_clock::rep time_since_epoch(){
    static_assert(
        std::is_integral<std::chrono::system_clock::rep>::value,
        "Representation of ticks isn't an integral value."
    );
    auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

int main(int argc, const char* argv[]) {
    // Modify the way to render them on screen:
 
    std::string reset_position;

    while(1) {
        auto component = vbox({
                window(text("stdstreams") | bold | center,
                        vbox({
                            hbox({
                           text(std::to_string(time_since_epoch())) | flex,
                           separator(),
                           text("skr") | flex,
                           }) | flex,
                           separator(),
                            hbox({
                           text("skr") | flex,
                           separator(),
                           text("skr") | flex,
                           }) | flex,
                           separator(),
                            hbox({
                           text("skr") | flex,
                           separator(),
                           text("skr") | flex,
                           }) | flex,
                           separator(),
                            hbox({
                           text("skr") | flex,
                           separator(),
                           text("skr") | flex,
                           }) | flex,
                           separator(),
                            hbox({
                           text("skr") | flex,
                           separator(),
                           text("skr") | flex,
                           }) | flex,
                            separator(),
                           text("skr"),
                           })) | flex,
        });
        auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
        Render(screen, component);
        std::cout << reset_position;
        screen.Print();
        reset_position = screen.ResetPosition();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
    return 0;
}

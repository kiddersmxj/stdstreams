#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
#include <memory>  // for shared_ptr, __shared_ptr_access
#include <string>  // for operator+, to_string

#include <stdlib.h>  // for EXIT_SUCCESS
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, Element, operator|, window, flex, vbox
 
#include <iostream>
#include <chrono>
#include <type_traits>

std::chrono::system_clock::rep time_since_epoch(){
    static_assert(
        std::is_integral<std::chrono::system_clock::rep>::value,
        "Representation of ticks isn't an integral value."
    );
    auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

using namespace ftxui;

int main(int argc, const char* argv[]) {
  int value = 50;
 
  // The tree of components. This defines how to navigate using the keyboard.
  auto buttons = Container::Horizontal({
      Button("Decrease", [&] { value--; }),
      Button("Increase", [&] { value++; }),
  });

  // Modify the way to render them on screen:
    auto component = vbox({
                window(text("stdstreams") | bold | center,
                        vbox({
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
                            hbox({
                           text("skr") | flex,
                           separator(),
                           text("skr") | flex,
                           }) | flex,
                            separator(),
                           text("skr"),
                           })) | flex,
    });
 
    std::string reset_position;
    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    Render(screen, component);
    while(1) {
        std::cout << reset_position;
        screen.Print();
        reset_position = screen.ResetPosition();
    };
    return 0;
}

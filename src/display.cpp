#include "../inc/display.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>
#include <string>
#include <cstring>

using namespace ftxui;

void Display::Print() {
    /* auto component = hbox({ */
    /*         window(text("stdstreams") | bold | center, */
    /*                 vbox(std::move(GetSectors()))) | flex */
    /*         }); */
    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    Render(screen, Screen);
    std::cout << ResetPosition;
    screen.Print();
    ResetPosition = screen.ResetPosition();
}

void Display::Create(Output Output) {
    std::vector<Element> IntElements;
    for(int i: Output.GetIntLocations())
        IntElements.push_back(IntElement(Output, i));
    Screen = vbox(IntElements);
}

Element Display::IntElement(Output Output, int Index) {
    Element Element;
    Element = hbox({
            window(text(Output.GetIntName(Index)),
                        text(std::to_string(Output.GetIntValue(Index)))
                            ) | flex });
    return Element;
}

std::vector<Element> GetSectors() {
    std::vector<Element> Screen;
    for(int i(0); i<10; i++) {
        if(i != 0)
            Screen.push_back(separator());
        Screen.push_back(vbox({
                    hbox(text("skr")) | flex
                  }) | flex);
    }
    return Screen;
}

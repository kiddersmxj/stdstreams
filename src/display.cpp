#include "../inc/display.hpp"
#include <vector>

using namespace ftxui;

void Display::Print() {
    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    Render(screen, Screen);
    std::cout << ResetPosition;
    screen.Print();
    ResetPosition = screen.ResetPosition();
}

void Display::Create(Output Output) {
	Decorator StatusStyle = size(HEIGHT, GREATER_THAN, 5);
    std::vector<Element> IntElements;
    std::vector<Element> StrElements;
    for(int i: Output.GetIntLocations())
        IntElements.push_back(GetIntElement(Output, i));
    for(int i: Output.GetStrLocations())
        StrElements.push_back(GetStrElement(Output, i));
    Screen = vbox({
            hbox({
                vbox(std::move(IntElements)) | flex,
                vbox(std::move(StrElements)),
                }) | flex,
				window(text("status"), vbox(std::move(GetStatElement(Output)))) | StatusStyle,
            });
}

std::vector<Element> GetStatElement(Output Output) {
	std::vector<Element> StatusElements;
	for(std::string s: Output.GetStatus()) {
		Element Element = text(s);
		StatusElements.push_back(Element);
	}
	return StatusElements;
}

Element GetStrElement(Output Output, int Index){
	Decorator StringStyle = size(WIDTH, GREATER_THAN, 20) | size(HEIGHT, GREATER_THAN, 30) | size(WIDTH, LESS_THAN, 50);
	Element Element = vbox({
			window(text(Output.GetName(Index)),
					text(Output.GetValue(Index))
					) | flex }) | StringStyle;
	return Element;
}

Element GetIntElement(Output Output, int Index) {
    Element Element = hbox({
            window(text(Output.GetName(Index)),
                        text(Output.GetValue(Index))
                            ) | flex }) | flex;
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

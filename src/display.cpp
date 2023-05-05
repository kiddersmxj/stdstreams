#include "../inc/display.hpp"

using namespace ftxui;

void Display::Print() {
}

void Display::Create(Output Output) {
	Decorator StatusStyle = size(HEIGHT, GREATER_THAN, 5);
    std::vector<Element> IntElements;
    std::vector<Element> StrElements;
    for(int i: Output.GetIntLocations())
        IntElements.push_back(GetIntElement(Output, i));
    for(int i: Output.GetStrLocations())
        StrElements.push_back(GetStrElement(Output, i));

        int GraphNo = 0;
    auto Graph = [&Output, &GraphNo](int width, int height) mutable {
        std::vector<int> Out(width);
#ifdef ICOUT
        std::cout << width << std::endl;
#endif
        int Iterator = Output.GetIntLocations().at(GraphNo);
#ifdef ICOUT
        std::cout << "It: " << Iterator << std::endl;
        std::cout << "size: " << Output.GetInts().at(Iterator).size() << "*********" << std::endl;
#endif
        for(int i=0; i<width; i++) {
#ifdef ICOUT
            std::cout << i << ": ";
#endif
            if(Output.GetInts().at(Iterator).size() > i) {
#ifdef ICOUT
                std::cout << Output.GetInts().at(Iterator).at(i) << ",";
#endif
                int Value = Output.GetInts().at(Iterator).at(i);
                Out.at(i) = Value;
            } else {
#ifdef ICOUT
                std::cout << "0, ";
#endif
                Out.at(i) = -1;
            }
#ifdef ICOUT
            std::cout << Out.at(i) << ", ";
#endif
        }
#ifdef ICOUT
        std::cout << std::endl;
#endif
        return Out;
    };

    Screen = vbox({
            hbox({
                vbox(std::move(IntElements), graph(std::ref(Graph))) | flex,
                vbox(std::move(StrElements)),
                }) | flex,
				window(text("status"), vbox(std::move(GetStatElement(Output)))) | StatusStyle,
            });
    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    Render(screen, Screen);
#ifndef NODISPLAY
    std::cout << ResetPosition;
    screen.Print();
    ResetPosition = screen.ResetPosition();
#else
        std::cout << "***DISPLAY***" << std::endl;
#endif
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


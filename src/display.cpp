#include "../inc/display.hpp"
#include <ftxui/dom/node.hpp>

using namespace ftxui;

void Display::Print() {
}

void Display::Create(Output Output) {
	Decorator StatusStyle = size(HEIGHT, GREATER_THAN, 5);
    std::vector<Element> IntElements;
    std::vector<Element> StrElements;

    int GraphNo;
    auto Graph = [&Output, &GraphNo](int width, int height) {
        std::vector<int> Out(width);
        int Iterator = GraphNo;
        GraphNo++;
#ifdef ICOUT
        std::cout << width << std::endl;
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

    std::vector<Element> Graphs(Output.GetIntLocations().size());
#ifdef ICOUT
    std::cout << Graphs.size() << std::endl;
#endif
    for(int i=0; i<Output.GetInts().size(); i++) {
        GraphNo = i;
#ifdef ICOUT
        std::cout << GraphNo << std::endl;
#endif
        Graphs.at(i) = graph(std::ref(Graph)) | flex;
    }
    
#ifdef ICOUT
    std::cout << "Through" << std::endl;
#endif

    GraphNo = 0;
    int I = 0;
    for(int i: Output.GetIntLocations()) {
#ifdef ICOUT
        std::cout << "I" << I << " i" << i<< std::endl;
#endif
        Element Content = vbox({
            text(Output.GetValue(i)),
            vbox(Graphs.at(I)) | flex
        });
        Element Element = hbox({
            window(text(Output.GetName(i)),
            Content) | flex
            }) | flex;
        IntElements.push_back(Element);
        I++;
    }
    for(int i: Output.GetStrLocations())
        StrElements.push_back(GetStrElement(Output, i));

    Screen = vbox({
            hbox({
                vbox(std::move(IntElements)) | flex,
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


#include "../inc/display.hpp"

using namespace ftxui;

// Create screen and render
void Display::Create(Output Output) {
    // Vectors to store different types of Elements
    std::vector<Element> IntElements;
    std::vector<Element> StrElements;

    // Iterator to go through each graph for each value in lambda
    int GraphNo = 0;
    // Graph builder
    auto Graph = [&Output, &GraphNo](int width, int height) {
        // Final graph vector sized to width of graph as that is x on graph
        std::vector<int> Out(width);
        // Assign graph to an iterator and increment for next call as lambda is called at ftxui::render()
        int Iterator = GraphNo;
        GraphNo++;
#ifdef ICOUT
        std::cout << width << std::endl;
        std::cout << "It: " << Iterator << std::endl;
        std::cout << "size: " << Output.GetInts().at(Iterator).size() << "*********" << std::endl;
#endif
        // Populate Graph values
        for(int i=0; i<width; i++) {
#ifdef ICOUT
            std::cout << i << ": ";
#endif
            // If the point along the width has a value in the int vector
            // Used to make sure we do not graph values that arent present yet at program commencment
            if(Output.GetInts().at(Iterator).size() > i) {
#ifdef ICOUT
                std::cout << Output.GetInts().at(Iterator).at(i) << ",";
#endif
                int Value = Output.GetInts().at(Iterator).at(i);
                int Min = Output.GetMinInt(Iterator);
                // If min is non negative set it to zero so height above zero is shown on graph
                // Else the min negative value is used as graph lowest point
                if(Min > 0)
                    Min = 0;
                // Maps the value into the space the graph has on the screen, using min and max and height values
                Value = k::Map(Value, Min, Output.GetMaxInt(Iterator), 0, height);
                // Assigns value into final position in vector
                Out.at(i) = Value;
            } else {
#ifdef ICOUT
                std::cout << "0, ";
#endif
                // If value doesnt exist -1 doesnt show up on graph like 0 does
                Out.at(i) = -1;
            }
#ifdef ICOUT
            std::cout << Out.at(i) << ", ";
#endif
        }
#ifdef ICOUT
        std::cout << std::endl;
#endif
        // Return final graph vector of y values (x is heights)
        return Out;
    };

    // Vector to store ftxui::graphs
    std::vector<Element> Graphs(Output.GetIntLocations().size());
#ifdef ICOUT
    std::cout << Graphs.size() << std::endl;
#endif
    // For each int value (stored in vector)
    for(int i=0; i<Output.GetInts().size(); i++) {
        // Create graph using lambda and add to vector
        Graphs.at(i) = graph(std::ref(Graph)) | flex;
    }
    
#ifdef ICOUT
    std::cout << "Through" << std::endl;
#endif

    // Iterator for each int variable (incremented at end)
    int I = 0;
    // Constructs int elements
    for(int i: Output.GetIntLocations()) {
        std::vector<Element> Values;
        int CharsNum;
        // Creates old value cascade
        for(int k=0; k<NumOldValuesShown; k++) {
            // Compares to see if min or max values have the most number of characters to get CharsNum
            CharsNum = std::to_string(Output.GetMaxInt(I)).length();
            int CharsNumMin = std::to_string(Output.GetMinInt(I)).length();
            if(CharsNumMin > CharsNum)
                CharsNum = CharsNumMin;

            // I honestly have no idea how this works I cannot remember how I did this genius
            // Makes it all nicely spaced :))
            if(Output.GetNegFlag(Output.GetMinInt(I))) {
                CharsNum++;
                    if(stoi(Output.GetPreviousInt(I, k)) >= 0) {
                        Values.push_back(hbox(text(" ")));
                        CharsNum--;
                    }
            } else Values.push_back(hbox(text(" ")));

            // Adds old values with respective colours based on how old they are to vector
            Values.push_back(hbox(text(Output.GetPreviousInt(I, k)) | color(GreyColours[k])) | size(WIDTH, GREATER_THAN, CharsNum));
        }
#ifdef ICOUT
        std::cout << "I" << I << " i" << i<< std::endl;
#endif
        // Create many body of int content with cascade and graph
        Element Content = vbox({
            hbox({
                hbox(std::move(Values)),
                paragraphAlignRight(" "),
                // Gets special properties from Output class
                text(AvgTitle) | IntStyle, text( std::to_string(Output.GetAvgInt(I)) + "   "),
                text(MinTitle) | IntStyle, text(std::to_string(Output.GetMinInt(I)) + "   "),
                text(MaxTitle) | IntStyle, text(std::to_string(Output.GetMaxInt(I))),
                separatorEmpty(),
            }),
            separatorLight() | IntStyle,
            vbox(Graphs.at(I)) | flex
        });
        // Wraps int content in border and title
        Element Element = hbox({
            window(text(Output.GetName(i)),
            Content | TextStyle) | flex
            }) | IntStyle | flex;
        IntElements.push_back(Element);
        // Increments to build next int variable
        I++;
    }
    // Build string elements
    for(int i: Output.GetStrLocations())
        StrElements.push_back(GetStrElement(Output, i));

    // Build screen
    Screen = vbox({
            vbox({
                hbox(std::move(StrElements)),
                vbox(std::move(IntElements)) | flex,
                }) | flex,
                // Build status bar
				window(text(StatusTitle), vbox(std::move(GetStatElement(Output)))) | StatStyle | size(HEIGHT, GREATER_THAN, Output.GetMaxStatuses() + 2),
            });

    // ftxui screen creation and rendering
    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    Render(screen, Screen);
#ifndef NODISPLAY
    // Stops terminal scrolling
    std::cout << ResetPosition;
    screen.Print();
    ResetPosition = screen.ResetPosition();
#else
        std::cout << "***DISPLAY***" << std::endl;
#endif
}

// Build string elements
Element Display::GetStrElement(Output Output, int Index){
    std::string V = Output.GetValue(Index);
    // If the value had the no data mark as a placeholder print an empty slot
    if(!NoDataMarkInternal.compare(V))
        V = "";

	Element Element = vbox({
			window(text(Output.GetName(Index)),
					text(" " + V) | TextStyle
					) | StrStyle | flex }) | flex;

	return Element;
}

// Build status bar
std::vector<Element> Display::GetStatElement(Output Output) {
	std::vector<Element> StatusElements;
    // Adds all status text to status vector
	for(std::string s: Output.GetStatus()) {
		Element Element = text(" " + s) | TextStyle;
		StatusElements.push_back(Element);
	}
	return StatusElements;
}


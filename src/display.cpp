/* Copyright (c) 2023, Maxamilian Kidd-May */
/* All rights reserved. */

/* This source code is licensed under the MIT license found in the */
/* LICENSE file in the root directory of this source tree. */ 

#include "../inc/display.hpp"
#include <ctime>

using namespace ftxui;

// Create screen and render
void Display::Create(Output Output, Child Child) {

    // Iterator to go through each graph for each value in lambda
    int GraphNo = 0;
    // Graph builder
    auto Graph = [&Output, &GraphNo](int width, int height) {
        // Final graph vector sized to width of graph as that is x on graph
        std::vector<int> Out(width);
        // Assign graph to an iterator and increment for next call as lambda is called at ftxui::render()
        int Iterator = GraphNo;
        GraphNo++;

        // Populate Graph values
        for(int i=0; i<width; i++) {
            // If the point along the width has a value in the int vector
            // Used to make sure we do not graph values that arent present yet at program commencment
            if(Output.GetInts().at(Iterator).size() > i) {
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

            // If value doesnt exist -1 doesnt show up on graph like 0 does
            } else Out.at(i) = -1;
        }
        // Return final graph vector of y values (x is heights)
        return Out;
    };

    auto r = Renderer([&Output, &Graph, this] {
        // Vectors to store different types of Elements
        std::vector<Element> IntElements;
        std::vector<Element> StrElements;

        // Vector to store ftxui::graphs
        std::vector<Element> Graphs(Output.GetIntLocations().size());
        /* std::cout << Output.GetIntLocations().size() << std::endl; */

        // For each int value (stored in vector)
        for(int i=0; i<Output.GetInts().size(); i++) {
            /* std::cout << "skr" << std::endl; */
            // Create graph using lambda and add to vector
            /* std::cout << Graphs.size() << std::endl; */
            Graphs.at(i) = graph(std::ref(Graph)) | flex;
        }
        
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
                if(k::IsNegative(Output.GetMinInt(I))) {
                    CharsNum++;
                        if(stoi(Output.GetPreviousInt(I, k)) >= 0) {
                            Values.push_back(hbox(text(" ")));
                            CharsNum--;
                        }
                } else Values.push_back(hbox(text(" ")));

                // Adds old values with respective colours based on how old they are to vector
                Values.push_back(hbox(text(Output.GetPreviousInt(I, k)) | color(GreyColours[k])) | size(WIDTH, GREATER_THAN, CharsNum));
            }

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

        // Build status bar
        Element Status = window(text(StatusTitle), vbox({
                            std::move(GetStatElement(Output))
                            })) | StatStyle | size(HEIGHT, GREATER_THAN, 
                            Output.GetMaxStatuses() + 2),

        // Build screen
        Screen = vbox({
                vbox({
                    hbox(std::move(StrElements)),
                    vbox(std::move(IntElements)) | flex,
                    vbox(Status)
                    }) | flex,
                });
        return Screen;
    });

    // ftxui screen creation and rendering
    auto screen = ScreenInteractive::Fullscreen();

    bool refresh_ui_continue = true;
    std::thread refresh_ui([&] {
        while(refresh_ui_continue) {
            // The |shift| variable belong to the main thread. `screen.Post(task)`
            // will execute the update on the thread where |screen| lives (e.g. the
            // main thread). Using `screen.Post(task)` is threadsafe.
            /* std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nfnldk\n"; */
            GraphNo = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(ProgramLatency));
            screen.Post([&] { Output.Parse(Child.Read()); });
            /* std::cout << Output.GetValue(1) << std::endl; */
            // After updating the state, request a new frame to be drawn. This is done
            // by simulating a new "custom" event to be handled.
            screen.Post(Event::Custom);
            if(!refresh_ui_continue) {
                screen.ExitLoopClosure()();
                std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\niwblnka\n";
            }
        }
    });

    /* auto renderer = Renderer([Screen] { return Screen; }); */
    r = CatchEvent(r, [&](Event event) {
        if (event == Event::Character('q')) {
            /* screen.Post([&] { Output.Parse(Child.Read()); }); */
            /* screen.ExitLoopClosure()(); */
            refresh_ui_continue = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            /* screen.Post([&] { Output.Parse(Child.Read()); }); */
            return true;
        }
        return false;
    });
    /* auto screen = Screen::Create(Dimension::Full(), Dimension::Full()); */
    /* Render(screen, Screen); */
#ifndef NODISPLAY
    // Stops terminal scrolling
    /* std::cout << ResetPosition; */
    /* screen.Print(); */
    /* ResetPosition = screen.ResetPosition(); */
    screen.Loop(r);
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


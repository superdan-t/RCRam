/* 
 * RCRam Control Station
 * 
 * Copyright (c) Daniel Tierney <sdme.cc> | All Rights Reserved
 * 
 * Usage of this source code, compiled binaries, and related assets is governed
 * by the license distributed with this code. If you did not receive a license
 * with this code, please contact the owner listed above with the location where
 * this source code was aquired.
 * 
 * The libraries used in this project are the properties of their respective
 * owners. Usage of libraries distributed with or linked to by this source code
 * may be governed by license separate from that of this source code. Where
 * applicable, these licenses are distributed with this source code.
 * 
 * THE OMISSION OF THIS HEADER STATEMENT DOES NOT IMPLY THAT THE FOLLOWING CODE
 * IS NOT SUBJECT TO THESE TERMS
 * 
 */

#define LAUNCH 0

#if   LAUNCH == 0
#include <nanogui/nanogui.h>
#include <devconsole/console.hpp>
#include <iostream>
#include <thread>
#include "gui/launcher.hpp"
#include "gui/main_window.hpp"
#elif LAUNCH == 1
#include "remotecontrol/video_example.hpp"
#elif LAUNCH == 2
#include "gui/widgets/formatted_text_buf.hpp"
#include <devconsole/console.hpp>
#include <sstream>
#include <iostream>
#endif

int main(void) {
#if   LAUNCH == 0
	GuiSessionConfig config;
	
	if (!glfwInit()) {
		return -1;
	}

	Launcher launch(config);

	if (!launch.isCancelled()) {
		MainWindow& mw = MainWindow::createMainWindow(config);
		mw.setup();

		std::thread consoleThread([]() {
			com::Console console;
			for (;;) {
				std::string input;
				std::getline(std::cin, input);
				console.readInput(input);
			}
		});

		mw.mainLoop();
		consoleThread.join();

	}
	
	glfwTerminate();
	return 0;
#elif LAUNCH == 1
	std::string fname;
	std::cin >> fname;
	cmain(fname.c_str());
	return 0;
#elif LAUNCH == 2
	std::ostringstream out;
	com::Console console(&out, &out);
	FormattedTextBuf textDisplay(500);

	for (;;) {
		std::string input;
		std::getline(std::cin, input);
		console.readInput(input);
		textDisplay.write(out.str());
		out.str("");
		out.clear();
		size_t txtSize = textDisplay.size();
		for (size_t i = 0; i < txtSize; ++i) {
			std::cout << textDisplay[i];
		}
		std::cout << std::endl;
	}
	return 0;
#endif

}

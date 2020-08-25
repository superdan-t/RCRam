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

#include <nanogui/nanogui.h>
#include <iostream>
#include "gui/launcher.hpp"
#include "gui/main_window.hpp"

int main(void) {
	GuiSessionConfig config;
	
	if (!glfwInit()) {
		return -1;
	}
	
	Launcher launcher(config);

	MainWindow& mw = MainWindow::createMainWindow(config);
	mw.setup();
	mw.mainLoop();
	
	glfwTerminate();
	return 0;
}

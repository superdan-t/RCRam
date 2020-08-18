#include "launcher.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <nanogui/nanogui.h>

Launcher::Launcher(GuiSessionConfig& config) {
	using namespace nanogui;
	
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Control Station Launcher", nullptr, nullptr);
	if (window == nullptr) {
		// TODO exception + handling
		std::cerr << "FATAL: Could not create window for launcher." << std::endl;
		return;
	}
	glfwMakeContextCurrent(window);
	
	static Screen screen;
	screen.initialize(window, false);
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapInterval(0);
	glfwSwapBuffers(window);
	
	FormHelper* form = new FormHelper(&screen);
	ref<Window> nanowindow = form->addWindow(Vector2i(0, 0), "");
	
	form->addGroup("Connection");
	form->setFixedSize(Vector2i(150, 20));
	form->addVariable("Address", config.network.address);
	form->addVariable("Port", config.network.port);
	
	form->addGroup("Window");
	form->setFixedSize(Eigen::Vector2i(65, 20));
	auto t = form->addVariable("Width", config.window.width);
	t->setMinValue(640);
	t->setUnits("px");
	t = form->addVariable("Height", config.window.height);
	t->setMinValue(480);
	t->setUnits("px");
	
	// Populate monitor selector
	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	std::vector<std::string> items;
	items.reserve(count);
	items.push_back("1 (Primary)");
	std::vector<std::string> items_short;
	items_short.reserve(count);
	items_short.push_back("1");
	for (int i = 1; i < count; i++) {
		auto s = std::to_string(i + 1);
		items.push_back(s);
		items_short.push_back(s);
	}
	auto monitorSelect = form->addVariable("Monitor", config.window.monitor);
	monitorSelect->setItems(items, items_short);
	
	form->addVariable("Fullscreen", config.window.fullscreen);
	
	form->addButton("Start", [&window]() { glfwSetWindowShouldClose(window, GL_TRUE); } );
	
	screen.setVisible(true);
	screen.performLayout();
	Vector2i winSize = nanowindow->size();
	glfwSetWindowSize(window, winSize(0, 0), winSize(1, 0));
	screen.setSize(winSize);
	
	makePopupCompact(screen, monitorSelect);
	
	glfwSetCursorPosCallback(window,
            [](GLFWwindow *, double x, double y) {
            screen.cursorPosCallbackEvent(x, y);
        }
    );

    glfwSetMouseButtonCallback(window,
        [](GLFWwindow *, int button, int action, int modifiers) {
            screen.mouseButtonCallbackEvent(button, action, modifiers);
        }
    );

    glfwSetKeyCallback(window,
        [](GLFWwindow *, int key, int scancode, int action, int mods) {
            screen.keyCallbackEvent(key, scancode, action, mods);
        }
    );

    glfwSetCharCallback(window,
        [](GLFWwindow *, unsigned int codepoint) {
            screen.charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(window,
        [](GLFWwindow *, int count, const char **filenames) {
            screen.dropCallbackEvent(count, filenames);
        }
    );

    glfwSetScrollCallback(window,
        [](GLFWwindow *, double x, double y) {
            screen.scrollCallbackEvent(x, y);
       }
    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *, int width, int height) {
            screen.resizeCallbackEvent(width, height);
        }
    );
	
	while (!glfwWindowShouldClose(window)) {
		glfwWaitEvents();
		
		glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		screen.drawContents();
		screen.drawWidgets();
		glfwSwapBuffers(window);
	}
	
}

void Launcher::makePopupCompact(const nanogui::Screen& screen, nanogui::PopupButton* button) {
	// The enumeration popup widget's default position is on the right side of its parent widget (usually a window)
	// There is only one window here, so it starts is out of view
	// This will move it back on the screen
	nanogui::Vector2i anchor = button->position();
	anchor(0, 0) = anchor(0, 0) + button->width();
	anchor(1, 0) = anchor(1, 0) + button->height() / 2;
	auto screen_width = screen.width();
	auto popup_width = button->popup()->width();
	if (anchor(0, 0) + popup_width > screen_width) {
		anchor(0, 0) = screen_width - popup_width;
	}
	auto screen_height = screen.height();
	auto popup_height = button->popup()->height();
	if (anchor(1, 0) + popup_height > screen_height) {
		button->popup()->setAnchorHeight(anchor(1, 0) + popup_height - screen_height);
	}
	button->popup()->setAnchorPos(anchor);
}

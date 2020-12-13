#include "main_window.hpp"

#include <iostream>

#include "console_window.hpp"

MainWindow* MainWindow::instance = nullptr;

MainWindow& MainWindow::createMainWindow(GuiSessionConfig& config) {
	if (instance)
		std::cout << "Warning: Attempt to create a second instance of the main window was ignored." << std::endl;
	else
		instance = new MainWindow(config);
	return *instance;
}

MainWindow& MainWindow::getInstance() {
	return *instance;
}

MainWindow::MainWindow(GuiSessionConfig& config) : config(config) {
	
}

void MainWindow::setup() {
	glfwWindowHint(GLFW_RESIZABLE, config.window.fullscreen ? GL_FALSE : GL_TRUE);

	int count;
	GLFWmonitor** monitors = glfwGetMonitors(&count);
	if ((int) config.window.monitor >= count) {
		std::cout << "Warning: Selected monitor does not exist. The primary monitor will be used instead." << std::endl;
		config.window.monitor = GuiSessionConfig::window_settings::Monitor::PRIMARY;
	}
	window = glfwCreateWindow(config.window.width, config.window.height, "Control Station", config.window.fullscreen ? monitors[ (size_t) config.window.monitor] : nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "FATAL: Could not create window for launcher." << std::endl;
		return;
	}
	glfwMakeContextCurrent(window);

	screen.initialize(window, false);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapInterval(0);
	glfwSwapBuffers(window);

	screen.setVisible(true);
	screen.performLayout();

	glfwSetCursorPosCallback(window, cursor_pos);
	glfwSetMouseButtonCallback(window, mouse_button);
	glfwSetKeyCallback(window, key);
	glfwSetCharCallback(window, char_callback);
	glfwSetDropCallback(window, drop);
	glfwSetScrollCallback(window, scroll);
	glfwSetFramebufferSizeCallback(window, framebuffer_size);

}

void MainWindow::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		instance->screen.drawContents();
		instance->screen.drawWidgets();
		glfwSwapBuffers(window);
	}
}

void MainWindow::cursor_pos(GLFWwindow* window, double x, double y) {
	instance->screen.cursorPosCallbackEvent(x, y);
}

void MainWindow::mouse_button(GLFWwindow* window, int button, int action, int modifiers) {
	instance->screen.mouseButtonCallbackEvent(button, action, modifiers);
}

void MainWindow::key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	instance->screen.keyCallbackEvent(key, scancode, action, mods);
}

void MainWindow::char_callback(GLFWwindow* window, unsigned int codepoint) {
	instance->screen.charCallbackEvent(codepoint);
}

void MainWindow::drop(GLFWwindow* window, int count, const char** filenames) {
	instance->screen.dropCallbackEvent(count, filenames);
}

void MainWindow::scroll(GLFWwindow* window, double x, double y) {
	instance->screen.scrollCallbackEvent(x, y);
}

void MainWindow::framebuffer_size(GLFWwindow* window, int width, int height) {
	instance->screen.resizeCallbackEvent(width, height);
}
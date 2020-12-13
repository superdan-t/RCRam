#pragma once

#include <nanogui/nanogui.h>
#include <devconsole/console.hpp>

#include "gui_config.hpp"

class MainWindow {
public:
	static MainWindow& createMainWindow(GuiSessionConfig& config);
	static MainWindow& getInstance();
	void setup();
	void mainLoop();
protected:
	MainWindow(GuiSessionConfig& config);
	GuiSessionConfig& config;
	GLFWwindow* window = nullptr;
	nanogui::Screen screen;

	// GLFW Callbacks
	static void cursor_pos(GLFWwindow* window, double x, double y);
	static void mouse_button(GLFWwindow* window, int button, int action, int modifiers);
	static void key(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void char_callback(GLFWwindow* window, unsigned int codepoint);
	static void drop(GLFWwindow* window, int count, const char** filenames);
	static void scroll(GLFWwindow* window, double x, double y);
	static void framebuffer_size(GLFWwindow* window, int width, int height);
private:
	static MainWindow* instance;

};
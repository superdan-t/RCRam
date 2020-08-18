#pragma once

#include <nanogui/nanogui.h>
#include <string>

#include "gui_config.hpp"

class Launcher {
public:
	Launcher(GuiSessionConfig& config);
private:
	static void makePopupCompact(const nanogui::Screen& screen, nanogui::PopupButton* button);
};

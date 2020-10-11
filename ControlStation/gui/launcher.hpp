#pragma once

#include <nanogui/nanogui.h>
#include <string>

#include "gui_config.hpp"

class Launcher {
public:
	Launcher(GuiSessionConfig& config);
	inline bool isCancelled() const { return cancelled; }
private:
	bool cancelled = true;
	static void makePopupCompact(const nanogui::Screen& screen, nanogui::PopupButton* button);
};

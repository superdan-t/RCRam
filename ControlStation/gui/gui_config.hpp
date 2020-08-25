#pragma once

#include "../remotecontrol/session_config.hpp"  

class GuiSessionConfig : public SessionConfig {
public:
	GuiSessionConfig() {
		
	}
	struct window_settings {
		window_settings() {
			width = 640;
			height = 480;
			monitor = Monitor::PRIMARY;
			fullscreen = false;
		}
		int width;
		int height;
		enum Monitor { PRIMARY = 0 } monitor;
		bool fullscreen;
	} window;
};

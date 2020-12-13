#pragma once

#include "../remotecontrol/session_config.hpp"

#include <boost/property_tree/ptree.hpp>

class GuiSessionConfig : public SessionConfig {
public:
	GuiSessionConfig() {}
	GuiSessionConfig(const boost::property_tree::ptree& pt) : SessionConfig(pt) {
		window.width = pt.get<int>("window.width", window.width);
		window.height = pt.get<int>("window.height", window.height);
		window.monitor = (window_settings::Monitor) pt.get<int>("window.monitor", window.monitor);
		window.fullscreen = pt.get<bool>("window.fullscreen", window.fullscreen);
	}
	void save(boost::property_tree::ptree& pt) {
		SessionConfig::save(pt);
		pt.put("window.width", window.width);
		pt.put("window.height", window.height);
		pt.put("window.monitor", (int)window.monitor);
		pt.put("window.fullscreen", window.fullscreen);
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

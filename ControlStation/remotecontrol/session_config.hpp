#pragma once

#include <string>

class SessionConfig {
public:
	struct {
		std::string address;
		std::string port;
		enum { LOCAL=0, WANET=1, PROXY=2 } mode;
	} network;
};

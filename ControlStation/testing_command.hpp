#pragma once

#include "devconsole/command.hpp"

#include <cstdlib>

class TestCommand : public ctrl::Command {
public:
	TestCommand() {
		name = "echot";
	}

	void execute(ctrl::Console* console, std::vector<std::string>& args) override {
		if (args.size() == 0) {
			*(console->out) << "Hello, world!" << std::endl;
		}
		else {
			*(console->out) << args[0] << std::endl;
		}
	}

	std::string getHelp() override {
		return "EchoT[est] will print \"Hello, world!\" if no argument is provided, or will print the first argument.";
	}
};
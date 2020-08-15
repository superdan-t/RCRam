#pragma once

#include <string>
#include <vector>

namespace ctrl {

class Console;

class Command {
public:
	std::string name;
	virtual void execute(Console* console, std::vector<std::string>& args) = 0;
	virtual std::string getHelp() = 0;
};

}	// end namespace ctrl

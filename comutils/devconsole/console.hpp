#pragma once

#include "command.hpp"
#include "console_input_errors.hpp"

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>

namespace com {

class Console {
public:
	Console(std::ostream* out, std::ostream* err);
	Console() : Console(&std::cout, &std::cerr) {};
	std::ostream* out;
	std::ostream* err;
	void registerCommand(Command* cmd);
	void removeCommand(Command& cmd);
	void removeCommand(std::string name);
	Command* getCommand(std::string name);
	void readInput(std::string instr);
	void (*clearCallback)(Console*) = 0;
	void (*inputErrorCallback)(Console*, InputError, std::string&) = 0;
	std::map<std::string, Command*> cmds;
	~Console();
private:
	static std::vector<std::string> getArgs(std::string inStr, std::string* cmdName);
};

} // end namespace com
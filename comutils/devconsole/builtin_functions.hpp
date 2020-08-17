#pragma once

#include "command.hpp"
#include "console_input_errors.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace com {

class Console;

class BuiltinClear : public Command {
public:
	BuiltinClear() {
		name = "clear";
	}
	void execute(Console* console, std::vector<std::string>& args) override {
		if (args.empty()) {
			console->clearCallback(console);
		}
		else {
			*(console->err) << "[built-in] clear: No options expected" << std::endl;
		}
	};
	std::string getHelp() override {
		return "Clears the screen. No options expected";
	};
};

class BuiltinHelp : public Command {
public:
	BuiltinHelp() {
		name = "help";
	}
	void execute(Console* console, std::vector<std::string>& args) override {
		if (args.empty()) {
			*(console->out) << "[built-in] help: Showing all topics" << std::endl;
			for (auto it = console->cmds.begin(); it != console->cmds.end(); ++it) {
				*(console->out) << "\t" << it->first << " -" << std::endl << "\t\t" << it->second->getHelp() << std::endl;
			}
		}
		else {
			Command* helpRequested = console->getCommand(args[0]);
			if (helpRequested != nullptr) {
				*(console->out) << "[built-in] help: Showing topics matching " << helpRequested->name << std::endl
					<< std::endl << helpRequested->getHelp() << std::endl;
			}
			else {
				*(console->out) << "[built-in] help: No topics matching " << args[0] << std::endl;
			}
		}
	};
	std::string getHelp() override {
		return "Display information about commands. If an argument is supplied, help for a matching command is provided. Otherwise, all commands are listed.";
	};
};

void defaultClearCallback(Console* console) {
#ifdef _WIN32
	std::system("cls");
#else
	std::system("clear");
#endif
}

void defaultInputErrorCallback(Console* console, InputError error, std::string& badInput) {
	switch (error) {
	case ESCAPE_UNRECOGNIZED:
		*(console->err) << "'\\" << badInput << "'" << ": invalid escape sequence" << std::endl;
		break;
	case NO_COMMAND:
		*(console->err) << badInput << ": command not found" << std::endl;
		break;
	case NOT_IMPLEMENTED:
		*(console->err) << badInput << ": built-in command not implemented" << std::endl;
		break;
	default:
		if (badInput.length() != 0) {
			*(console->err) << badInput << ": ";
		}
		*(console->err) << "invalid input (no reason provided)" << std::endl;
	}
}

} // end namespace com
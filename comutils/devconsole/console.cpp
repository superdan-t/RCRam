#include "console.hpp"
#include "builtin_functions.hpp"
#include "exceptions/duplicate_command_exception.hpp"
#include "exceptions/invalid_name_command_exception.hpp"
#include "exceptions/input_exception.hpp"

#include <iterator>
#include <iostream>

namespace com {

Console::Console(std::ostream* out, std::ostream* err) {
	this->out = out;
	this->err = err;
	clearCallback = &defaultClearCallback;
	inputErrorCallback = &defaultInputErrorCallback;
	registerCommand(new BuiltinClear);
	registerCommand(new BuiltinHelp);
}

void Console::registerCommand(Command* cmd) {
	if (cmd->name.size() == 0) {
		throw InvalidNameCommandException(cmd->name, com::InvalidReason::EMPTY);
	}
	for (char& c : cmd->name) {
		if (!isalnum(c)) {
			throw InvalidNameCommandException(cmd->name, com::InvalidReason::ALNUM);
		}
	}
	if (cmds.count(cmd->name) > 0) {
		throw DuplicateCommandException(cmd->name);
	}
	cmds.emplace(cmd->name, cmd);
}

void Console::removeCommand(Command& cmd) {
	delete getCommand(cmd.name);
	cmds.erase(cmd.name);
}

void Console::removeCommand(std::string name) {
	delete getCommand(name);
	cmds.erase(name);
}

Command* Console::getCommand(std::string name) {
	for (auto it = cmds.find(name); it != cmds.end(); ++it) {
		return it->second;
	}
	return nullptr;
}

void Console::readInput(std::string instr) {
	try {
		std::string cmdName = "";
		auto args = getArgs(instr, &cmdName);
		if (!cmdName.empty()) {
			auto cmd = getCommand(cmdName);
			if (cmd != nullptr) {
				cmd->execute(this, args);
			}
			else {
				throw InputException(NO_COMMAND, cmdName);
			}
		}
	}
	catch (InputException e) {
		inputErrorCallback(this, e.error, e.badInput);
	}
}

Console::~Console() {
	for (auto it = cmds.begin(); it != cmds.end(); ++it) {
		delete it->second;
	}
	cmds.clear();
}

std::vector<std::string> Console::getArgs(std::string inStr, std::string* cmdName) {
	std::string current = "";
	std::vector<std::string> args;
	cmdName->clear();
	bool quoted = false;
	for (int i = 0; i < inStr.length(); i++) {
		if (inStr[i] == '\\') {
			switch (inStr[++i]) {
			case ' ':
				current += ' ';
				break;
			case '\\':
				current += '\\';
				break;
			case '"':
				current += '"';
				break;
			case 'n':
				current += '\n';
				break;
			default:
				throw InputException(ESCAPE_UNRECOGNIZED, std::string(1,inStr[i]));
				break;
			}
		}
		else if (inStr[i] == '"') {
			quoted = !quoted;
		}
		else if (inStr[i] == ' ' && !quoted) {
			if (current.length() > 0) {
				if (cmdName->length() > 0) {
					args.push_back(current);
				}
				else {
					cmdName->assign(current);
				}
				current = "";
			}
		}
		else {
			current += inStr[i];
		}
	}
	if (cmdName->length() > 0) {
		args.push_back(current);
	}
	else {
		cmdName->assign(current);
	}
	return args;
}

} // end namespace com
#include "duplicate_command_exception.hpp"

namespace ctrl {

DuplicateCommandException::DuplicateCommandException(std::string dupedCommandName) {
	this->dupedCommandName = dupedCommandName;
}

std::string DuplicateCommandException::getMessage() const {
	return "Attempted to register a duplicate command: " + dupedCommandName;
}

} // end namespace ctrl
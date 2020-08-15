#include "invalid_name_command_exception.hpp"

namespace ctrl {

InvalidNameCommandException::InvalidNameCommandException(std::string badName, InvalidReason reason) {
	this->badName = badName;
	this->reason = reason;
}

std::string InvalidNameCommandException::getMessage() const {
	switch (reason) {
	case ALNUM:
		return "Attempted to register a command with invalid name: \"" + badName + "\" (names must be alphanumeric)";
	case EMPTY:
		return "Attempted to register a command with no name (must have a unique name)";
	default:
		return "Attempted to register a command with an invalid name (no reason specified)";
	}
}

} // end namespace ctrl
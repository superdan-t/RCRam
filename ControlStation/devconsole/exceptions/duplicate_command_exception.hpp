#pragma once
#include "command_exception.hpp"

#include <string>

namespace ctrl {

class DuplicateCommandException : public CommandException {
public:
	DuplicateCommandException(std::string dupedCommandName);
	std::string getMessage() const override;
private:
	std::string dupedCommandName;
};

}
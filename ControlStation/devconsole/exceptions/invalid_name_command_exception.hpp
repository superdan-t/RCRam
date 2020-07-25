#pragma once
#include "command_exception.hpp"

namespace ctrl {

enum InvalidReason {
	ALNUM,
	EMPTY
};

class InvalidNameCommandException : public CommandException {
public:
	InvalidNameCommandException(std::string badName, InvalidReason reason);
	std::string getMessage() const override;
private:
	std::string badName;
	InvalidReason reason;
};

}
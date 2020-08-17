#pragma once
#include "command_exception.hpp"

namespace com {

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
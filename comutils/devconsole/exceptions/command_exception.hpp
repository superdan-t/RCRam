#pragma once

#include <exception>
#include <string>

namespace com {

class CommandException : public std::exception {
public: 
	virtual std::string getMessage() const = 0;
};

} // end namespace com
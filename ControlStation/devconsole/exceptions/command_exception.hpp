#pragma once

#include <exception>
#include <string>

namespace ctrl {

class CommandException : public std::exception {
public: 
	virtual std::string getMessage() const = 0;
};

} // end namespace ctrl
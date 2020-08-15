#pragma once

#include "../console_input_errors.hpp"

#include <string>

namespace ctrl {
class InputException {
public:
	InputError error;
	std::string badInput;
	InputException(InputError error, std::string badInput) {
		this->error = error;
		this->badInput = badInput;
	};
};
}

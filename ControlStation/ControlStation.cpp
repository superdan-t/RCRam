/*#include <iostream>

#include "devconsole/console.hpp"
#include "devconsole/command.hpp"

#include "testing_command.hpp"

int main(void) {
	ctrl::Console console;
	ctrl::Command* test = new TestCommand;
	console.registerCommand(test);

	while (true) {
		std::cout << "$ ";
		std::string userInput;
		std::getline(std::cin, userInput);
		console.readInput(userInput);
		std::cout << std::endl;
	}

	return 0;
}*/

#include <string.h>
#include <iostream>

#include <network/message.hpp>
int main(void) {
	using namespace com;
	MessageExchange ex("127.0.0.1", "50446");
	Message toSend;
	toSend.data = new char[6];
	strncpy(toSend.data, "Hen lo", 6);
	toSend.data[3] = 2;
	toSend.dataLen = 6;
	toSend.typeName = "test";
	toSend.typeNameLen = 4;

	if (toSend.data == nullptr) std::cerr << "Lost data!" << std::endl;
	ex.send(toSend);
	for (;;);
}

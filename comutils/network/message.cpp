#include "message.hpp"

#define CONTROL_CHAR(x) 

#include <iostream>
#include <string.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

namespace com {
    
Message::Message(const char* typeName, char* data, size_t dataLen) {
	if (typeName == nullptr) {
		typeNameLen = 0;
	} else {
		typeNameLen = strlen(typeName);
	}
	this->typeName = typeName;
	this->data = data;
	this->dataLen = dataLen;
}

char* const Message::serialize(size_t* size) {
	*size = 3 + dataLen + typeNameLen;
	*size += escapesRequired(data, dataLen);
	*size += escapesRequired(typeName, typeNameLen);
	char* odata = new char[*size];
	odata[0] = SOH;
	size_t i = 1;
	for (int j = 0; j < typeNameLen; ++j) {
		if (controlChar(typeName[j])) {
			odata[i] = ESC;
			odata[i + 1] = typeName[j];
			i += 2;
		}
		else {
			odata[i++] = typeName[j];
		}
	}
	odata[i++] = STX;
	for (int j = 0; j < dataLen; ++j) {
		if (controlChar(data[j])) {
			odata[i] = ESC;
			odata[i + 1] = data[j];
			i += 2;
		}
		else {
			odata[i++] = data[j];
		}
	}
	odata[i] = ETX;
	return odata;
}

const bool Message::controlChar(char c) {
	return c >= SOH && c <= EOT || c == ESC;
}

const size_t Message::escapesRequired(const char* str, size_t len) {
	size_t req = 0;
	for (int i = 0; i < len; ++i) {
		if (controlChar(str[i])) {
			++req;
		}
	}
	return req;
}

MessageExchange::MessageExchange(std::string hostname, std::string port) : tSendMessages(&MessageExchange::run, this) {
	this->hostname = hostname;
	this->port = port;
}

void MessageExchange::send(Message m) {
	queueMtx.lock();
	queue.push_back(m);
	queueMtx.unlock();
}

void MessageExchange::run() {
	try {
		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		tcp::resolver::results_type endpoints = resolver.resolve(hostname, port);
		tcp::socket socket(io_context);

		for (;;) {
			if (!queue.empty() && !paused) {
				// Add queued Messages to a new vector so that queue can keep operating in main thread
				queueMtx.lock();
				std::vector<Message> outgoing = queue;
				queue.clear();
				queueMtx.unlock();

				boost::asio::connect(socket, endpoints);
				for (auto it = outgoing.begin(); it != outgoing.end(); ++it) {
					size_t olen = 0;
					char* omsg = it->serialize(&olen);
					socket.send(boost::asio::buffer(omsg, olen));
					delete[] it->data;
					delete[] omsg;
				}
				socket.send(boost::asio::buffer(&EOT, 1));
				
				// Receive until connection is closed
				for (;;) {
					boost::array<char, 128> buf;
					boost::system::error_code error;

					size_t len = socket.read_some(boost::asio::buffer(buf), error);
					if (error == boost::asio::error::eof) {
						std::cout << "Connection closed." << std::endl;
						break;
					}
					else if (error) {
						throw boost::system::system_error(error);
					}

				}

			}
		}
	}
	catch (boost::system::system_error& e) {
		std::cerr << "An error occurred while exchanging messages:" << e.what() << std::endl;
		// TODO: Throw this error again once appropriate handling is implemented
	}

}

MessageExchange::~MessageExchange() {
	tSendMessages.join();
}

} // end namespace com

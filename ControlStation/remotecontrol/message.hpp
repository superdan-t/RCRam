#pragma once

#include <vector>
#include <mutex>
#include <thread>
#include <string>
#include <boost/asio/buffer.hpp>

namespace ctrl {

constexpr char ESC = 0x1B;
constexpr char SOH = 0x01;
constexpr char STX = 0x02;
constexpr char ETX = 0x03;
constexpr char EOT = 0x04;

class Message {
public:
	Message(const char* typeName, char* data, size_t dataLen);
	Message() : Message(nullptr, nullptr, 0) {};
	char* data;
	const char* typeName;
	size_t dataLen;
	size_t typeNameLen;
	char* const serialize(size_t* size);
	static bool const controlChar(char c);
	static size_t const escapesRequired(const char* str, size_t len);
};

class MessageExchange {
public:
	MessageExchange(std::string host, std::string port);
	std::mutex queueMtx;
	bool paused = false;
	void send(Message m);
	~MessageExchange();
private:
	std::vector<Message> queue;
	std::thread tSendMessages;
	std::string hostname;
	std::string port;
	void run();
};

} // end namespace ctrl

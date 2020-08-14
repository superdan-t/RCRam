#pragma once

#include "message.hpp"

namespace ctrl {

enum class MotionControlMode {
	STOPPED = 0,
	MANUAL = 1
};

enum class MotionDirection {
	BACKWARD = -1,
	STOPPED = 0,
	FORWARD = 1
};

class Motion {
public:
	Motion(MessageExchange& msg);
	void setMode(MotionControlMode m);
	void drive(MotionDirection direction, double throttle);
	void steer(double heading);
private:
	MotionControlMode mode;
	static constexpr char* DRIVE_CMD = "drive";
	static constexpr char* STEER_H_CMD = "steerh";
	static constexpr double THROTTLE_MAX = 100.0;
	static constexpr double THROTTLE_MIN = 0.0;
	static constexpr double HEADING_MAX = 90.0;
	static constexpr double HEADING_MIN = -90.0;

	MessageExchange* msg;
};

} // end namepsace ctrl
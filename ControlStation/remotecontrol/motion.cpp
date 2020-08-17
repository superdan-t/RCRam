#include "motion.hpp"

namespace ctrl {

Motion::Motion(com::MessageExchange& msg) {
	this->msg = &msg;
}

void Motion::drive(MotionDirection direction, double throttle) {
	if (throttle > THROTTLE_MAX) throttle = THROTTLE_MAX;
	else if (throttle < THROTTLE_MIN) throttle = THROTTLE_MIN;
	char* data = new char[1 + sizeof(double)];
	data[0] = (char)direction;
	data[1] = throttle;
	msg->send(com::Message(DRIVE_CMD, data, 1 + sizeof(double)));
}

void Motion::steer(double heading) {
	if (heading > HEADING_MAX) heading = HEADING_MAX;
	else if (heading < HEADING_MIN) heading = HEADING_MIN;
	char* data = new char[sizeof(double)];
	data[0] = heading;
	msg->send(com::Message(STEER_H_CMD, data, sizeof(double)));
}

} // end namespace ctrl

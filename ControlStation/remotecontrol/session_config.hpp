#pragma once

#include <string>
#include <boost/property_tree/ptree.hpp>

class SessionConfig {
public:
	SessionConfig() {}
	SessionConfig(const boost::property_tree::ptree& pt) {
		network.address = pt.get<std::string>("network.remote_ip", "");
		network.port = pt.get<std::string>("network.remote_port", "");
		std::string mode = pt.get<std::string>("network.mode", "");
		if (mode == "WANET") mode = network.WANET;
		else if (mode == "PROXY") mode = network.PROXY;
		else mode = network.LOCAL;
	}
	void save(boost::property_tree::ptree& pt) {
		pt.put("network.remote_ip", network.address);
		pt.put("network.remote_port", network.port);
		if (network.mode == network.WANET) pt.put("network.mode", "WANET");
		else if (network.mode == network.PROXY) pt.put("network.mode", "WANET");
		else pt.put("network.mode", "LOCAL");
	}
	struct {
		std::string address;
		std::string port;
		enum { LOCAL=0, WANET=1, PROXY=2 } mode;
	} network;
};

#ifndef __YEELINK_API_
#define __YEELINK_API_

#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "json\json.hpp"
#include "read_url_boost.hpp"

class YEELINK_API
{
public:
	YEELINK_API();
	~YEELINK_API();
	static double read_lastvalue(int device_id, int sensor_id);

private:
	static std::string read_lastdata(int device_id, int sensor_id);
};

YEELINK_API::YEELINK_API()
{
}

YEELINK_API::~YEELINK_API()
{
}

double YEELINK_API::read_lastvalue(int device_id, int sensor_id) {
	double result = -1.0;
	std::string str;
	do {
		str = read_lastdata(device_id, sensor_id);
	} while (str.empty());

	try {
		nlohmann::json jj = nlohmann::json::parse(str.c_str());
		/*for (json::iterator it = j3.begin(); it != j3.end(); ++it) {
		std::cout << it.key() << " : " << it.value() << "\n";
		}*/
		result = jj["value"];
	}
	catch(char*){}
	return result;
}

std::string YEELINK_API::read_lastdata(int device_id, int sensor_id) {
	std::stringstream ss, sss;

	std::string sRemoteFilePath = "/v1.0/device/";
	std::string device;
	ss << device_id;
	ss >> device;
	sRemoteFilePath += device;
	sRemoteFilePath += "/sensor/";
	std::string sensor;
	sss << sensor_id;
	sss >> sensor;
	sRemoteFilePath += sensor;
	sRemoteFilePath += "/datapoints";

	return READ_URL_BOOST::read_url("api.yeelink.net", sRemoteFilePath);
}



#endif // !__YEELINK_API_




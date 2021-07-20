#pragma once
#include "winsock2.h"
#include <string>
using PortValue = uint16_t;

struct UDPData
{
	//udp variables
	WSADATA wsaData;
	SOCKET clientSocket;
	addrinfo hints;
	PortValue port{ 80 };
	addrinfo* clientInfo = nullptr;

	//change later
	std::string hostName{ "2000" };
};

class UDP
{
	//all udp data
	UDPData data;

public:

	//stages for udp boot up
	void StartUp();
	void GetAddressInfo(const std::string& clientHostPort);
	void CreateSocket();


};


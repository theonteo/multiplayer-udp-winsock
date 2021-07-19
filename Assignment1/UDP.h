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
	std::string hostName{ "localhost" };
};

class UDP
{
	//all udp data
	UDPData data;

public:

	//stages for udp boot up
	void StartUp();
	void GetAddressInfo();
	void CreateSocket();


};


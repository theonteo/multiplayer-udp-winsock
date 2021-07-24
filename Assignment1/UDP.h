/*****************************************************************************/
/*!
\file
\author
\par email:
\par DigiPen login:
\par Course: cs260
\par Assignment 4
\date

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

#pragma once

#include "winsock2.h"
#include <string>

using PortValue = uint16_t;
class GameObject;

struct UDPData
{
	//udp variables
	WSADATA wsaData;
	SOCKADDR_IN localAddress;
	SOCKET socket;
	addrinfo hints;
	addrinfo* info = nullptr;

	//save address info
	sockaddr_in receiveAddress;
	sockaddr_in sendAddress;

	//change later
	std::string hostName{ "2000" };
	size_t portNumber{ 0 };
};

class UDP
{
protected:
	//all udp data
	UDPData data;

public:

	//stages for udp boot up
	virtual void StartUp(const std::string& port ="") = 0;

	~UDP() = default;

};


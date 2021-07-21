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
	SOCKET clientSocket;
	addrinfo hints;
	PortValue port{ 80 };
	addrinfo* clientInfo = nullptr;
	addrinfo* serverInfo = nullptr;
	//change later
	std::string hostName{ "2000" };
	size_t portNumber{ 0 };
};

class UDP
{
	//all udp data
	UDPData data;

public:

	//stages for udp boot up
	void StartUp();
	void GetAddressInfo(const std::string& clientHostPort);

	void CreateClientSocket();
	void CreateServerSocket();

	void Send(const GameObject& player);
	void Receive();
};


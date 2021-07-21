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

#include "UDP.h"

#include <stdlib.h>
#include <crtdbg.h>
#include <functional>

#include "Player.h"
#include "Packet.h"
#include "GameObject.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Windows.h"		
#include "ws2tcpip.h"		

#pragma comment(lib, "ws2_32.lib")
#include "Exceptions.h"

namespace
{
	sockaddr_in broadcast_addr;

	constexpr int port = 9999;
}


void UDP::StartUp()
{
	int errorCode = WSAStartup(MAKEWORD(2, 2), &data.wsaData);

	if (errorCode != NO_ERROR)
		throw
		exceptionHandler("WSAStartup() failed.", errorCode);

#ifdef PRINTDEBUG
	std::cout
		<< "Winsock version: "
		<< static_cast<int>(LOBYTE(udp.wsaData.wVersion))
		<< "."
		<< static_cast<int>(HIBYTE(udp.wsaData.wVersion))
		<< "\n"
		<< std::endl;
#endif
}

void UDP::GetAddressInfo(const std::string& clientHostPort)
{
	size_t portNum = std::atoi(clientHostPort.c_str());

	if (!portNum)
		throw exceptionHandler("Incorrect port number", 1);

	// Object hints indicates which protocols to use to fill in the info.
	SecureZeroMemory(&data.hints, sizeof(data.hints));
	data.hints.ai_family = AF_INET;			// IPv4
	// For TCP use SOCK_STREAM instead of SOCK_DGRAM.
	data.hints.ai_socktype = SOCK_DGRAM;		// Best effort
	// Could be 0 for autodetect, but best effort over IPv4 is always UDP.
	data.hints.ai_protocol = IPPROTO_UDP;	// UDP

	int errorCode = getaddrinfo(nullptr,
		clientHostPort.c_str(), &data.hints, &data.clientInfo);

	//no error - pass number to data struct
	data.portNumber = portNum;

	if (errorCode || !data.clientInfo)
	{
		//exception handling
		throw
			exceptionHandler
			("getaddrinfo() failed.", errorCode);
	}
}

void UDP::CreateSocket()
{
	data.clientSocket = socket(
		data.hints.ai_family, data.hints.ai_socktype,
		data.hints.ai_protocol);

	if (data.clientSocket == INVALID_SOCKET)
		throw
		exceptionHandler("socket() failed.", 1);

	//reuse port
//broadcast option
	char broadcast = 1;
	setsockopt
	(data.portNumber, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

	int errorCode = bind(
		data.clientSocket,
		data.clientInfo->ai_addr,
		static_cast<int>(data.clientInfo->ai_addrlen));

	if (errorCode != NO_ERROR)
	{
		closesocket(data.clientSocket);
		data.clientSocket = INVALID_SOCKET;
	}

	freeaddrinfo(data.clientInfo);

	if (data.clientSocket == INVALID_SOCKET)
		throw
		exceptionHandler("bind() failed.", 2);
}

void UDP::Receive()
{
	if (!data.clientSocket)
		return;

	sockaddr clientAddress{};
	SecureZeroMemory(&clientAddress, sizeof(clientAddress));
	int clientAddressSize = sizeof(clientAddress);

	constexpr size_t BUFFER_SIZE = 5000;
	char buffer[BUFFER_SIZE]{ 0 };
	const int bytesReceived = recvfrom(data.clientSocket,
		buffer,
		BUFFER_SIZE - 1,
		0,
		&clientAddress, &clientAddressSize);
	if (bytesReceived > 0)
	{
		int x = 0;
	}


	Packet packetData = *reinterpret_cast<Packet*>(buffer);
}

void UDP::Send(const GameObject& player)
{

	int addr_len = sizeof(struct sockaddr_in);

	memset((void*)&broadcast_addr, 0, addr_len);
	broadcast_addr.sin_family = AF_INET;
	broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	broadcast_addr.sin_port = htons(port);

	//broadcast option
	char broadcast = 1;
	setsockopt
	(data.portNumber, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

	//find current player

	//placeholder testing
	Packet packet{ MoveType::MOVE_DOWN,player.translate };

	const int bytesSent =
		sendto(data.clientSocket, reinterpret_cast<char*>(&packet),
			sizeof(Packet), 0,
			(struct sockaddr*) &broadcast_addr, sizeof(broadcast_addr));

	if (bytesSent == SOCKET_ERROR)
	{
		//throw exceptionHandler("no bytes are sent", 2);
	}
	else
	{
		int x = 0;
	}
}

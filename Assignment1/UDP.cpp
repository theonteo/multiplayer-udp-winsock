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
#define _WINSOCK_DEPRECATED_NO_WARNINGS
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


namespace Client
{
	SOCKET socketD;
	SOCKET socketC;

	hostent* h;
	
	sockaddr_in clientAddr;
	sockaddr_in serverAddr;
	constexpr int usedPort = 9999;
	std::string host{ "localhost" };
}


namespace Server
{
	SOCKET socketD;
	SOCKET socketC;


	sockaddr_in clientAddr;
	sockaddr_in serverAddr;
	constexpr int usedPort = 9999;
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
	/*
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
	*/
}

void UDP::CreateClientSocket()
{
	/*
	///size_t portNum = std::atoi(Client::host.c_str());

	//if (!portNum)
	//	throw exceptionHandler("Incorrect port number", 1);

	// Object hints indicates which protocols to use to fill in the info.
	SecureZeroMemory(&data.hints, sizeof(data.hints));
	data.hints.ai_family = AF_INET;			// IPv4
	// For TCP use SOCK_STREAM instead of SOCK_DGRAM.
	data.hints.ai_socktype = SOCK_DGRAM;		// Best effort
	// Could be 0 for autodetect, but best effort over IPv4 is always UDP.
	data.hints.ai_protocol = IPPROTO_UDP;	// UDP

	int errorCode = getaddrinfo(nullptr,
		std::to_string(Client::usedPort).c_str() , &data.hints, &data.clientInfo);

	//no error - pass number to data struct
	data.portNumber = Client::usedPort;

	if (errorCode || !data.clientInfo)
	{
		//exception handling
		throw
			exceptionHandler
			("getaddrinfo() failed.", errorCode);
	}

	Client::socketD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (Client::socketD == INVALID_SOCKET)
	{
		throw
			exceptionHandler("socket() failed.", 1);
	}
	char broadcast = 1;
	if (setsockopt
	(Client::socketD, SOL_SOCKET, SO_BROADCAST,
		&broadcast, sizeof(broadcast)) == -1)
	{
		throw
			exceptionHandler("setsockopt() failed.", 1);
	}

	Client::clientAddr.sin_family = AF_INET;
	Client::clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	Client::clientAddr.sin_port = htons(0);

	Client::socketC = bind(Client::socketD, (struct sockaddr*) & Client::clientAddr,
		sizeof(Client::clientAddr));

	if (Client::socketC == INVALID_SOCKET)
	{
		throw
			exceptionHandler("bind() failed.", 1);
	}
	*/
}

void UDP::CreateServerSocket()
{
	// Object hints indicates which protocols to use to fill in the info.
	SecureZeroMemory(&data.hints, sizeof(data.hints));
	data.hints.ai_family = AF_INET;			// IPv4
	// For TCP use SOCK_STREAM instead of SOCK_DGRAM.
	data.hints.ai_socktype = SOCK_DGRAM;		// Best effort
	// Could be 0 for autodetect, but best effort over IPv4 is always UDP.
	data.hints.ai_protocol = IPPROTO_UDP;	// UDP

	int errorCode = getaddrinfo(nullptr,
		std::to_string(Server::usedPort).c_str(), &data.hints, &data.serverInfo);

	//no error - pass number to data struct
	if (errorCode || !data.serverInfo)
	{
		//exception handling
		throw
			exceptionHandler
			("getaddrinfo() failed.", errorCode);
	}

	Server::socketD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (Server::socketD == INVALID_SOCKET)
	{
		throw
			exceptionHandler("socket() failed.", 1);
	}

	char broadcast = 1;

	if (setsockopt
	(Server::socketD, SOL_SOCKET, SO_BROADCAST,
		&broadcast, sizeof(broadcast)) == -1)
	{
		throw
			exceptionHandler("setsockopt() failed.", 1);
	}

	
	//Server::serverAddr.sin_family = AF_INET;
	//Server::serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//Server::serverAddr.sin_port = htons(Server::usedPort);
	

	Server::socketC = bind(Server::socketD, data.serverInfo->ai_addr,
		static_cast<int>(data.serverInfo->ai_addrlen));

	if (Server::socketC == INVALID_SOCKET)
	{
		throw
			exceptionHandler("bind() failed.", 1);
	}
}


//void UDP::CreateSocket()
//{
	/*
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
		*/
//}

void UDP::Receive()
{
	/*
	constexpr size_t BUFFER_SIZE = 5000;
	int len = sizeof(Server::clientAddr);

	char buffer[BUFFER_SIZE]{ 0 };
	const int bytesReceived = recvfrom(Server::socketD,
		buffer,
		BUFFER_SIZE - 1,
		0,
		(sockaddr*)&Server::clientAddr, &len);
	if (bytesReceived > 0)
	{
		int x = 0;
	}
	*/

	

	/*
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
	*/
}

void UDP::Send(const GameObject& player)
{

	int addr_len = sizeof(struct sockaddr_in);

	//placeholder testing
	Packet packet{ MoveType::MOVE_DOWN,glm::vec3(0,0,0) };


	sockaddr serverAddress{};
	serverAddress = *data.serverInfo->ai_addr;
	int serverAddressSize = sizeof(serverAddress);

	const int bytesSent =
		sendto(Server::socketD, reinterpret_cast<char*>(&packet),
			sizeof(Packet), 0,
			&serverAddress, serverAddressSize);

	if (bytesSent == SOCKET_ERROR)
	{
		throw exceptionHandler("no bytes are sent", 2);
	}
	else
	{
		int x = 0;
	}


}

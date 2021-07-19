#include "UDP.h"

#include <stdlib.h>
#include <crtdbg.h>
#include <functional>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Windows.h"		
#include "ws2tcpip.h"		

#pragma comment(lib, "ws2_32.lib")
#include "Exceptions.h"

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

void UDP::GetAddressInfo()
{
	// Object hints indicates which protocols to use to fill in the info.
	SecureZeroMemory(&data.hints, sizeof(data.hints));
	data.hints.ai_family = AF_INET;			// IPv4
	// For TCP use SOCK_STREAM instead of SOCK_DGRAM.
	data.hints.ai_socktype = SOCK_DGRAM;		// Best effort
	// Could be 0 for autodetect, but best effort over IPv4 is always UDP.
	data.hints.ai_protocol = IPPROTO_UDP;	// UDP

	int errorCode = getaddrinfo(nullptr,
		data.hostName.c_str(), &data.hints, &data.clientInfo);
	if (errorCode || !data.clientInfo)
	{
		//exception handling
		throw
			exceptionHandler("getaddrinfo() failed.", errorCode);
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
	const int opt = 1;
	setsockopt
	(data.clientSocket, SOL_SOCKET, SO_REUSEADDR,
		(char*)&opt, sizeof(opt));

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

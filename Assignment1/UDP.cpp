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

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Windows.h"		
#include "ws2tcpip.h"		

#pragma comment(lib, "ws2_32.lib")
#include "Exceptions.h"



void UDP::StartUp(const std::string& port)
{
	int errorCode = WSAStartup(MAKEWORD(2, 2), &data.wsaData);

	if (errorCode != NO_ERROR)
		throw
		exceptionHandler("WSAStartup() failed.", errorCode);


	char broadcast = '1';

	data.socket = socket(AF_INET, SOCK_DGRAM, 0);

	if (setsockopt(data.socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
	{
		closesocket(data.socket);
		throw
			exceptionHandler("setsockopt() failed", errorCode);
	}
	if (setsockopt(data.socket, SOL_SOCKET, SO_REUSEADDR, &broadcast, sizeof(broadcast)) < 0)
	{
		closesocket(data.socket);
		throw
			exceptionHandler("setsockopt() failed", errorCode);
	}

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

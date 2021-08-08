/******************************************************************************/
/*!
\file SocketAddress.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\par email: c.choo\@digipen.edu
\par email: kevin.hartono\@digipen.edu
\par email: zhengyongtheon.teo\@digipen.edu

\par DigiPen login: c.choo
\par DigiPen login: kevin.hartono
\par DigiPen login: zhengyongtheon.teo

\par Course: CS260-A
\par Assignment 4
\date 01/08/2021
\brief
This file contains the definitions of the Socket Address class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "SocketAddress.h"
#include "Exceptions.h"

SocketAddress::SocketAddress(const std::string& _sockAddr)
{
	size_t colonIndex = _sockAddr.find(':');

	ip = _sockAddr.substr(0, colonIndex);
	port = _sockAddr.substr(colonIndex + 1);

	// Retrieve address
	addrinfo hints{};
	SecureZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;			// IPv4
	hints.ai_socktype = SOCK_DGRAM;		// Best effort
	hints.ai_protocol = IPPROTO_UDP;	// UDPint

	addrinfo* info = nullptr;

	int errorCode =
		getaddrinfo(ip.c_str(), port.c_str(), &hints, &info);

	if ((errorCode != NO_ERROR) || (info == nullptr))
	{
		WSACleanup();
		throw exceptionHandler("getaddrinfo() failed.", errorCode);
	}

	// Save sockaddr information
	sockAddr = *info->ai_addr;
	addrLen = info->ai_addrlen;

	// Save IPv4 dot format
	const sockaddr_in* socketAddrPtr =
		reinterpret_cast<const sockaddr_in*>(&sockAddr);

	char buffer[16];
	inet_ntop(AF_INET, &socketAddrPtr->sin_addr, buffer, 15);
	buffer[15] = '\0';
	ip = buffer;

	freeaddrinfo(info);
}

SocketAddress::SocketAddress(const sockaddr& _sockAddr) :
	sockAddr{ _sockAddr }
{
	const sockaddr_in* socketAddrPtr =
		reinterpret_cast<const sockaddr_in*>(&_sockAddr);

	char buffer[16];
	inet_ntop(AF_INET, &socketAddrPtr->sin_addr, buffer, 15);
	buffer[15] = '\0';
	ip = buffer;
	port = std::to_string(ntohs(socketAddrPtr->sin_port));
}

bool operator==(const SocketAddress& lhs, const SocketAddress& rhs)
{
	return
		lhs.ip == rhs.ip &&
		lhs.port == rhs.port;
}

bool operator!=(const SocketAddress& lhs, const SocketAddress& rhs)
{
	return !(lhs == rhs);
}

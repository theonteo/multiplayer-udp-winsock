/*****************************************************************************/
/*!
\file SocketAddress.h

\author Bryan Choo
\author Kevin Hartono
\author Teo Zheng Yong Theon

\par Course: cs260
\par Assignment 4
\date 1/8/21

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Windows.h"
#include "ws2tcpip.h"

#pragma comment(lib, "ws2_32.lib")

#include <string>

struct SocketAddress
{
	std::string ip;
	std::string port;
  sockaddr sockAddr{};
	size_t addrLen = 0;
	
	SocketAddress() = default;
	SocketAddress(const std::string& _sockAddr);
	SocketAddress(const sockaddr& _sockAddr);
};

bool operator==(const SocketAddress& lhs, const SocketAddress& rhs);
bool operator!=(const SocketAddress& lhs, const SocketAddress& rhs);

namespace std
{
    // Hashing function used to hash SocketAddress for std::unordered_map
    template <>
    struct hash<SocketAddress>
    {
        std::size_t operator()(const SocketAddress& socketAddress) const
        {
            return (
                (hash<string>()(socketAddress.ip) ^
                (hash<string>()(socketAddress.port) << 1)));
        }
    };
}
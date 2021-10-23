/******************************************************************************/
/*!
\file SocketAddress.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

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
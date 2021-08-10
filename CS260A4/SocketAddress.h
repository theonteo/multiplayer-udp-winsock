/******************************************************************************/
/*!
\file SocketAddress.h
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
This file contains the declarations of the Socket Address class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
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
/*/*****************************************************************************/
/*!
\file Player.h

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
#include <string>
#include <array>
#include <chrono>
#include "Packet.h"

enum class MoveType : unsigned char;

struct PingData
{
	unsigned long index{ 0 };
	std::chrono::system_clock::time_point start{};
	std::chrono::system_clock::time_point end{};
};

class Player
{
public:
	static constexpr unsigned int PING_ARRAY_SIZE = 20;
	static constexpr unsigned int MAX_MISSED_PING = 20;

	//Flag to check if player is currently connected
	bool isConnected{ false };

	//Counter to keep track of latest packet index
	unsigned int latestPacket{ 0 };

	//connection timeout
	float connectionTimer{ 0.0f };

	//player score
	int score{ 0 };

	//Counter to keep track of lasest ping index
	unsigned int latestPingIndex{ 0 };

	//Array to keep track of latest ping data
	std::array<PingData, PING_ARRAY_SIZE> latestPings{ 0 };

	//Counter to keep track of how many missed pings
	unsigned int missedPings{ 0 };

	float GetAveragePing();
};


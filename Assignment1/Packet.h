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

#ifndef _PACKET_H_
#define _PACKET_H_

#include <vector>
#include<string>
#include <glm.hpp>
#include "Player.h"
using PacketData = std::vector<char>;
class Player;
enum class PacketType
{
	PACKET_DATA = 1,
	PACKET_TERMINATE = 2,
	PACKET_ACK = 3,
	PACKET_UNKNOWN,
};

enum class MoveType
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
};

struct Packet
{
	char hostName[50];
	int hostNameLength{ 0 };

	//change what to send!!!
	MoveType moveType;
	glm::vec3 position;

	Player playerData;

	Packet() = default;
	Packet(const char* hostName, const MoveType& type,
		const Player& player, const glm::vec3& pos);
};

struct dataPacket :public Packet
{
	dataPacket() = default;
	dataPacket(const PacketData& packetdata);
	int sequence;
	int length;

	//store payload
	std::vector<char> data;
};

#endif
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

#include <glm.hpp>
#include <WinSock2.h>
#include <array>
#include <algorithm>
#include "Player.h"
#include "CommonValues.h"

enum class PacketType : unsigned char
{
	CONNECTION_REQUEST = 1,
	CONNECTION_REPLY,
	CONNECTION_CONFIRMATION,
	CONNECTION_NOTIFICATION,
	DATA_PACKET,

	NUM_OF_PACKET_TYPES			// Must be last
};

enum class MoveType : unsigned char
{
	MOVE_UP = 1,
	MOVE_DOWN = 2,
	MOVE_LEFT = 4,
	MOVE_RIGHT = 8,
	KILL = 16
};

struct Packet
{
	const PacketType packetType;

	Packet(PacketType _packetType);

	virtual void NtoH() = 0;
	virtual void HtoN() = 0;
};

struct ConnectionPacket : Packet
{
	ConnectionPacket();

	virtual void NtoH() override;
	virtual void HtoN() override;
};

struct ConnectionReply : Packet
{
	unsigned short assignedID;

	unsigned short playerIndices[MAX_PEER];
	unsigned short ports[MAX_PEER];
	IN_ADDR ips[MAX_PEER];

	ConnectionReply();

	virtual void NtoH() override;
	virtual void HtoN() override;
};

struct ConnectionConfirmation : Packet
{
	unsigned short assignedID = 0;

	ConnectionConfirmation();

	virtual void NtoH() override;
	virtual void HtoN() override;
};

struct ConnectionNotification : Packet
{
	unsigned short joiningID = 0;

	unsigned short port = 0;
	IN_ADDR ip{};

	ConnectionNotification();

	virtual void NtoH() override;
	virtual void HtoN() override;
};

struct DataPacket : Packet
{
	unsigned char moveInfo{};
	glm::vec3 position{};

	DataPacket();

	virtual void NtoH() override;
	virtual void HtoN() override;
};

namespace
{
	constexpr std::array
	<
		size_t,
		static_cast<size_t>(PacketType::NUM_OF_PACKET_TYPES)
	> packetSizes
	{
		sizeof(ConnectionPacket),
		sizeof(ConnectionReply),
		sizeof(ConnectionConfirmation),
		sizeof(ConnectionNotification),
		sizeof(DataPacket)
	};
}

constexpr size_t MAX_PACKET_SIZE =
	*std::max_element(packetSizes.begin(), packetSizes.end());

#endif
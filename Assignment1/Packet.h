/*****************************************************************************/
/*!
\file Packet.h

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

#ifndef _PACKET_H_
#define _PACKET_H_

#include <glm.hpp>
#include <WinSock2.h>
#include <array>
#include <algorithm>
#include <random>
#include "Player.h"
#include "CommonValues.h"

enum class PacketType : unsigned char
{
	CONNECTION_REQUEST = 1,
	CONNECTION_REPLY,
	CONNECTION_CONFIRMATION,
	CONNECTION_NOTIFICATION,
	DATA_PACKET,
	INITIATE_LOCKSTEP,
	LOCKSTEP_DATA,
	HASHED_DATA,

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

struct InitiateLockstepPacket : Packet
{
	InitiateLockstepPacket();

	virtual void NtoH() override;
	virtual void HtoN() override;
};

struct LockstepDataPacket : Packet
{
private:
	// Random number generator to generate key
	static std::mt19937_64 uniformRandGen;
	static std::uniform_int_distribution<unsigned short> u_i_distribution;

	unsigned short collidingID{static_cast<unsigned short>(-1)};

	// Randomly generated key to ensure that the other clients
	// will not be able to brute force the hash
	unsigned short key{};

public:

	LockstepDataPacket();
	LockstepDataPacket& operator=(const LockstepDataPacket& rhs);

	void SetCollidingID(unsigned short _collidingID);
	unsigned short GetCollidingID() const;
	unsigned short GetKey() const;

	virtual void NtoH() override;
	virtual void HtoN() override;
};



struct HashedDataPacket : Packet
{
	size_t hashedData{};

	HashedDataPacket();
	HashedDataPacket& operator=(const HashedDataPacket& rhs);

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
		sizeof(DataPacket),
		sizeof(InitiateLockstepPacket),
		sizeof(LockstepDataPacket),
		sizeof(HashedDataPacket)
	};
}

constexpr size_t MAX_PACKET_SIZE =
	*std::max_element(packetSizes.begin(), packetSizes.end());

namespace std
{
	// Hashing function used to hash LockstepDataPacket
	template <>
	struct hash<LockstepDataPacket>
	{
		std::size_t operator()(const LockstepDataPacket& data) const
		{
			return
			(
				(hash<unsigned short>()(data.GetCollidingID())) ^
				(hash<short>()(data.GetKey()) << 1)
			);
		}
	};
}

#endif
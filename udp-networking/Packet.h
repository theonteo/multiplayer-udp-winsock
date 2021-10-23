/******************************************************************************/
/*!
\file Packet.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef _PACKET_H_
#define _PACKET_H_

#include <glm.hpp>
#include <WinSock2.h>
#include <array>
#include <algorithm>
#include <random>
#include <bitset>
#include "CommonValues.h"

enum class PacketType : unsigned char
{
	CONNECTION_REQUEST = 0,
	CONNECTION_REPLY,
	CONNECTION_CONFIRMATION,
	CONNECTION_NOTIFICATION,
	RECONNECTION_REPLY,
	DATA_PACKET,
	INITIATE_LOCKSTEP,
	LOCKSTEP_DATA,
	HASHED_DATA,
	DISCONNECT_NOTIFICATION,
	PING_PACKET,
	PING_REPLY,
	FORCE_DISCONNECT,

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
};

struct ConnectionPacket : Packet
{
	ConnectionPacket();

	void NtoH();
	void HtoN();
};

struct ConnectionReply : Packet
{
	unsigned short assignedID{ 0 };
	unsigned short hostID{ 0 };

	unsigned short playerIndices[MAX_PEER]{ 0 };
	unsigned short ports[MAX_PEER]{ 0 };
	IN_ADDR ips[MAX_PEER]{};

	ConnectionReply();

	void NtoH();
	void HtoN();
};

struct ConnectionConfirmation : Packet
{
	unsigned short assignedID = 0;

	ConnectionConfirmation();

	void NtoH();
	void HtoN();
};

struct ConnectionNotification : Packet
{
	unsigned short joiningID = 0;

	unsigned short port = 0;
	IN_ADDR ip{};

	ConnectionNotification();

	void NtoH();
	void HtoN();
};

struct ReconnectionReply : Packet
{
	static constexpr int MAX_ENABLED = (MAX_FOOD + MAX_PLAYER) / 8 + 1;

	unsigned short assignedID;
	unsigned short hostID{ 0 };
	unsigned short playerIndices[MAX_PEER];
	unsigned short ports[MAX_PEER];
	IN_ADDR ips[MAX_PEER];

	float gameTime = 0.0f;
	char isEnabled[MAX_ENABLED]{ false };
	char isConnected{ 0 };
	unsigned short lockstepID{ 0 };
	unsigned int latestPackets[MAX_PLAYER]{ 0 };
	unsigned short scores[MAX_PLAYER]{ 0 };
	unsigned char moveInfos[MAX_PLAYER]{ 0 };
	glm::vec3 positions[MAX_PLAYER]{};

	ReconnectionReply();

	void NtoH();
	void HtoN();
};

struct DataPacket : Packet
{
	unsigned int packetNum{ 0 };
	unsigned char moveInfo{};
	glm::vec3 position{};

	DataPacket();

	void NtoH();
	void HtoN();
};

struct InitiateLockstepPacket : Packet
{
	unsigned short lockstepID{ 0 };

	InitiateLockstepPacket();

	void NtoH();
	void HtoN();
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

	void NtoH();
	void HtoN();
};

struct HashedDataPacket : Packet
{
	size_t hashedData{};

	HashedDataPacket();
	HashedDataPacket& operator=(const HashedDataPacket& rhs);

	void NtoH();
	void HtoN();
};

struct DisconnectNotification : Packet
{
	DisconnectNotification();

	void NtoH();
	void HtoN();
};

struct PingPacket : Packet
{
	unsigned long pingIndex{ 0 };

	PingPacket();

	void NtoH();
	void HtoN();
};

struct PingReply : Packet
{
	unsigned long pingIndex{ 0 };

	PingReply();

	void NtoH();
	void HtoN();
};

struct ForceDisconnectPacket : Packet
{
	unsigned short playerID{ 0 };

	ForceDisconnectPacket();

	void NtoH();
	void HtoN();
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
		sizeof(ReconnectionReply),
		sizeof(ConnectionConfirmation),
		sizeof(ConnectionNotification),
		sizeof(DataPacket),
		sizeof(InitiateLockstepPacket),
		sizeof(LockstepDataPacket),
		sizeof(HashedDataPacket),
		sizeof(DisconnectNotification),
		sizeof(PingPacket),
		sizeof(PingReply),
		sizeof(ForceDisconnectPacket)
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
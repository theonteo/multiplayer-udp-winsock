/******************************************************************************/
/*!
\file Packet.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#include "Packet.h"
#include <WinSock2.h>

Packet::Packet(PacketType _packetType) :
	packetType{ _packetType }
{
	// Nothing to do here
}

ConnectionPacket::ConnectionPacket() :
	Packet{ PacketType::CONNECTION_REQUEST }
{
	// Nothing to do here
}

void ConnectionPacket::NtoH()
{
	// Nothing to do here
}

void ConnectionPacket::HtoN()
{
	// Nothing to do here
}

ConnectionReply::ConnectionReply() :
	Packet{ PacketType::CONNECTION_REPLY }
{
	// Nothing to do here
}

void ConnectionReply::NtoH()
{
	assignedID = ntohs(assignedID);
	hostID = ntohs(hostID);

	for (size_t i = 0; i < MAX_PEER; ++i)
	{
		playerIndices[i] = ntohs(playerIndices[i]);
		ports[i] = ntohs(ports[i]);
	}
}

void ConnectionReply::HtoN()
{
	assignedID = htons(assignedID);
	hostID = htons(hostID);

	for (size_t i = 0; i < MAX_PEER; ++i)
	{
		playerIndices[i] = htons(playerIndices[i]);
		ports[i] = htons(ports[i]);
	}
}

ConnectionConfirmation::ConnectionConfirmation() :
	Packet{ PacketType::CONNECTION_CONFIRMATION }
{
	// Nothing to do here
}

void ConnectionConfirmation::NtoH()
{
	assignedID = ntohs(assignedID);
}

void ConnectionConfirmation::HtoN()
{
	assignedID = htons(assignedID);
}

ConnectionNotification::ConnectionNotification() :
	Packet{ PacketType::CONNECTION_NOTIFICATION }
{
	// Nothing to do here
}

void ConnectionNotification::NtoH()
{
	joiningID = ntohs(joiningID);
	port = ntohs(port);
}

void ConnectionNotification::HtoN()
{
	joiningID = htons(joiningID);
	port = htons(port);
}

DataPacket::DataPacket() :
	Packet{ PacketType::DATA_PACKET }
{
	// Nothing to do here
}

void DataPacket::NtoH()
{
	packetNum = ntohl(packetNum);
	position.x = ntohf(*reinterpret_cast<unsigned int*>(&position.x));
	position.y = ntohf(*reinterpret_cast<unsigned int*>(&position.y));
	position.z = ntohf(*reinterpret_cast<unsigned int*>(&position.z));
}

void DataPacket::HtoN()
{
	packetNum = htonl(packetNum);
	unsigned int temp = htonf(position.x);
	position.x = *reinterpret_cast<float*>(&temp);
	temp = htonf(position.y);
	position.y = *reinterpret_cast<float*>(&temp);
	temp = htonf(position.z);
	position.z = *reinterpret_cast<float*>(&temp);
}

InitiateLockstepPacket::InitiateLockstepPacket() :
	Packet{ PacketType::INITIATE_LOCKSTEP }
{
	// Nothing to do here
}

void InitiateLockstepPacket::NtoH()
{
	lockstepID = ntohs(lockstepID);
}

void InitiateLockstepPacket::HtoN()
{
	lockstepID = htons(lockstepID);
}

std::mt19937_64 LockstepDataPacket::uniformRandGen{ std::random_device{}() };
std::uniform_int_distribution<unsigned short> LockstepDataPacket::u_i_distribution
{
	0,
	(std::numeric_limits<unsigned short>::max)()
};

LockstepDataPacket::LockstepDataPacket() :
	Packet{ PacketType::LOCKSTEP_DATA },
	key{ u_i_distribution(uniformRandGen) }
{
	// Nothing to do here
}

LockstepDataPacket& LockstepDataPacket::operator=(
	const LockstepDataPacket& rhs)
{
	collidingID = rhs.collidingID;
	key = rhs.key;

	return *this;
}

void LockstepDataPacket::SetCollidingID(unsigned short _collidingID)
{
	collidingID = _collidingID;
	key = u_i_distribution(uniformRandGen);
}

unsigned short LockstepDataPacket::GetCollidingID() const
{
	return collidingID;
}

unsigned short LockstepDataPacket::GetKey() const
{
	return key;
}

void LockstepDataPacket::NtoH()
{
	collidingID = ntohs(collidingID);
	key = ntohs(key);
}

void LockstepDataPacket::HtoN()
{
	collidingID = htons(collidingID);
	key = htons(key);
}

HashedDataPacket::HashedDataPacket() :
	Packet{ PacketType::HASHED_DATA }
{
	// Nothing to do here
}

HashedDataPacket& HashedDataPacket::operator=(
	const HashedDataPacket& rhs)
{
	hashedData = rhs.hashedData;
	return *this;
}

void HashedDataPacket::NtoH()
{
	hashedData = ntohll(hashedData);
}

void HashedDataPacket::HtoN()
{
	hashedData = htonll(hashedData);
}

DisconnectNotification::DisconnectNotification() :
	Packet{ PacketType::DISCONNECT_NOTIFICATION }
{
	// Nothing to do here
}

void DisconnectNotification::NtoH()
{
	// Nothing to do here
}

void DisconnectNotification::HtoN()
{
	// Nothing to do here
}

ReconnectionReply::ReconnectionReply() :
	Packet{ PacketType::RECONNECTION_REPLY }
{
}

void ReconnectionReply::NtoH()
{
	assignedID = ntohs(assignedID);
	hostID = ntohs(hostID);

	for (size_t i = 0; i < MAX_PEER; ++i)
	{
		playerIndices[i] = ntohs(playerIndices[i]);
		ports[i] = ntohs(ports[i]);
	}

	lockstepID = ntohs(lockstepID);
	gameTime = ntohf(*reinterpret_cast<unsigned int*>(&gameTime));
	
	for (size_t i = 0; i < MAX_PLAYER; ++i)
	{
		latestPackets[i] = ntohl(latestPackets[i]);
		scores[i] = ntohs(scores[i]);
		positions[i].x = ntohf(*reinterpret_cast<unsigned int*>(&positions[i].x));
		positions[i].y = ntohf(*reinterpret_cast<unsigned int*>(&positions[i].y));
		positions[i].z = ntohf(*reinterpret_cast<unsigned int*>(&positions[i].z));
	}
}

void ReconnectionReply::HtoN()
{
	assignedID = htons(assignedID);
	hostID = htons(hostID);

	for (size_t i = 0; i < MAX_PEER; ++i)
	{
		playerIndices[i] = htons(playerIndices[i]);
		ports[i] = htons(ports[i]);
	}

	lockstepID = htons(lockstepID);
	unsigned int temp = htonf(gameTime);
	gameTime = *reinterpret_cast<float*>(&temp);
		
	for (size_t i = 0; i < MAX_PLAYER; ++i)
	{
		latestPackets[i] = htonl(latestPackets[i]);
		scores[i] = htons(scores[i]);
		temp = htonf(positions[i].x);
		positions[i].x = *reinterpret_cast<float*>(&temp);
		temp = htonf(positions[i].y);
		positions[i].y = *reinterpret_cast<float*>(&temp);
		temp = htonf(positions[i].z);
		positions[i].z = *reinterpret_cast<float*>(&temp);
	}
}

PingPacket::PingPacket() :
	Packet{ PacketType::PING_PACKET }
{
	// Nothing to do here
}

void PingPacket::NtoH()
{
	pingIndex = ntohl(pingIndex);
}

void PingPacket::HtoN()
{
	pingIndex = htonl(pingIndex);
}

PingReply::PingReply() :
	Packet{ PacketType::PING_REPLY }
{
	// Nothing to do here
}

void PingReply::NtoH()
{
	pingIndex = ntohl(pingIndex);
}

void PingReply::HtoN()
{
	pingIndex = htonl(pingIndex);
}

ForceDisconnectPacket::ForceDisconnectPacket() :
	Packet{ PacketType::FORCE_DISCONNECT }
{
	// Nothing to do here
}

void ForceDisconnectPacket::NtoH()
{
	playerID = ntohs(playerID);
}

void ForceDisconnectPacket::HtoN()
{
	playerID = htons(playerID);
}
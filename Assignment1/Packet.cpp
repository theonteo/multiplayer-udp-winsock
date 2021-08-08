/*****************************************************************************/
/*!
\file Packet.cpp

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

	for (size_t i = 0; i < MAX_PEER; ++i)
	{
		playerIndices[i] = ntohs(playerIndices[i]);
		ports[i] = ntohs(ports[i]);
	}
}

void ConnectionReply::HtoN()
{
	assignedID = htons(assignedID);

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
	position.x = ntohf(*reinterpret_cast<unsigned int*>(&position.x));
	position.y = ntohf(*reinterpret_cast<unsigned int*>(&position.y));
	position.z = ntohf(*reinterpret_cast<unsigned int*>(&position.z));
}

void DataPacket::HtoN()
{
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
	// Nothing to do here
}

void InitiateLockstepPacket::HtoN()
{
	// Nothing to do here
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
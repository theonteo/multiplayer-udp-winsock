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
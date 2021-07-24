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
#include <sstream>

// -------------------------------------------------------------------------
// dataPacket::dataPacket(const PacketData& packetdata)
//
// constructor
// -------------------------------------------------------------------------
dataPacket::dataPacket(const PacketData& packetdata)
{
}

Packet::Packet
(const char* name, const MoveType& type, const glm::vec3& pos)
	: moveType{ type }, position{ pos }
{
	strcpy_s(hostName, name);
}

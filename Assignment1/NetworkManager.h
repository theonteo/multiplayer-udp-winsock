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
#pragma once

#include <string>
#include <vector>

#include "UDPReceive.h"
#include "UDPSend.h"

#include "Player.h"

class Player;

class NetworkManager
{
	std::vector<Player> playerData;

	UDPReceive udpReceive;
	UDPSend udpSend;

public:

	const std::vector<Player>& GetPlayerData() const;

	void Init(const std::vector<Player>& data);
	void Update();

	void Idle();
	void Send();
	void Receive();


	void UnpackPacket(const Packet& packet);

};


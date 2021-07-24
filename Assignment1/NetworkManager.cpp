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

#include "NetworkManager.h"
#include "Player.h"
#include "Packet.h"

#include <string>
#include <thread>
#include <functional>
#include "GameObjectManager.h"
#include "Exceptions.h"

namespace
{
	constexpr size_t clientPlayerNum{ 0 };
}

const std::vector<Player>& NetworkManager::GetPlayerData() const
{
	return playerData;
}

void NetworkManager::Init(const std::vector<Player>& data)
{
	playerData = data;
}

void NetworkManager::Update()
{
	udpReceive.StartUp();
	udpSend.StartUp();

	std::thread receiveThread
	(std::bind(&NetworkManager::Receive, this));

	std::thread sendThread
	(std::bind(&NetworkManager::Send, this));

	receiveThread.join();
	sendThread.join();
}

void NetworkManager::Send()
{
	while (1)
	{
		const auto& playerName = NetworkManager::GetPlayerData();
		if (playerName.empty()) continue;
		//placeholder testing - change to proper packet next time
		Packet packet
		{ playerName[0].GetPortName().c_str(), 
			MoveType::MOVE_DOWN,glm::vec3(0,5,0) };

		//send player info - for testing
		udpSend.Send(packet);
	}
}

void NetworkManager::Receive()
{
	while (1)
	{
		//keep receiving
		udpReceive.Receive();
	}
}

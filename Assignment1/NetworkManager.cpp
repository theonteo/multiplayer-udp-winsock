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
#include "Game.h"

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
	//get own port number
	udpReceive.StartUp(playerData[0].GetPortNumber());
	udpSend.StartUp(playerData[0].GetPortNumber());
	Game::InitPlayer(playerData[0].GetPortName());

	//keep receiving and send data

	std::thread receiveThread
	(std::bind(&NetworkManager::Receive, this));

	//only one thread needed due to broadcast
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

		//player container is empty ,don't send
		if (playerName.empty()) continue;

		//placeholder testing - change to proper packet next time

		const auto& iter = GameObjectManager::GameObjectList.find
		(playerName[0].GetPortName());

		//cannot find own player gameobject , don't send
		if (iter == GameObjectManager::GameObjectList.end())continue;

		//send player data
		Packet packet
		{ playerName[0].GetPortName().c_str(),
			MoveType::MOVE_DOWN,	iter->second->translate };

		//send player info - for testing
		udpSend.Send(packet);
	}
}

void NetworkManager::Receive()
{
	while (1)
	{
		//keep receiving packet then process them accordingly
		const auto& packet = udpReceive.Receive();

		//unpack and give data to gameplay containers(player pos etc)
		UnpackPacket(packet);
	}
}

void NetworkManager::UnpackPacket(const Packet& packet)
{
	//move this somewhere else

	//same person - return
	if (GameObjectManager::GameObjectList.empty() ||
		playerData[0].GetPortName() == packet.hostName)
		return;

	std::string temp
	{ packet.hostName,packet.hostName + packet.hostNameLength };

	const auto& iter = GameObjectManager::GameObjectList.find(temp);

	//cannot find player from gameobject container
	if (iter == GameObjectManager::GameObjectList.end())
		return;

	//update player position
	const auto& player = iter->second;
	player->translate = packet.position;
}

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
	//get own port number
	udpReceive.StartUp(playerData[0].GetPortNumber());
	udpSend.StartUp(playerData[0].GetPortNumber());
	
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
		//keep receiving packet then process them accordingly
		const auto& packet = udpReceive.Receive();

		//unpack and give data to gameplay containers(player pos etc)
		UnpackPacket(packet);
	}
}

void NetworkManager::UnpackPacket(const Packet& packet)
{

}

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

#include <string>
#include <thread>
#include <functional>
#include "GameObjectManager.h"
#include "Exceptions.h"

namespace
{
	constexpr size_t clientPlayerNum{ 0 };
}


void NetworkManager::Init(const std::vector<Player>& data)
{
	//udp.StartUp();

	//use player 
//	udp.GetAddressInfo(data[clientPlayerNum].GetPortNumber());

	//udp.CreateSocket();
}

void NetworkManager::Update()
{


	udp.StartUp();
	udp.CreateClientSocket();
	udp.CreateServerSocket();

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
		const auto& player =
			GameObjectManager::GameObjectList.find
			("Player" + std::to_string(clientPlayerNum));

		//cannot find client player
		if (player == GameObjectManager::GameObjectList.end())
			continue;

		//send player info - for testing
		udp.Send(*player->second);
	}
}

void NetworkManager::Receive()
{
	while (1)
	{
		udp.Receive();
	}
}

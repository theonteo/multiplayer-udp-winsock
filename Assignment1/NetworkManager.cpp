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
#define _CRT_SECURE_NO_WARNINGS
#include "NetworkManager.h"
#include "Player.h"
#include "Packet.h"

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <functional>
#include "GameState.h"
#include "GameObjectManager.h"
#include "Exceptions.h"
#include "Game.h"
#include "DeltaTime.h"
#include "CommonValues.h"

namespace
{
	constexpr size_t clientPlayerNum{ 0 };
	std::mutex mutex;
	std::string clientPlayer;
}

const std::map<std::string, Player>& NetworkManager::GetPlayerData() const
{
	return playerData;
}

void NetworkManager::Init
(const std::string& clientName,  const std::map<std::string, Player>& data)
{
	clientPlayer = clientName;
	playerData = data;
}

void NetworkManager::Update()
{
	const auto& portNum = playerData.find(clientPlayer)->second.portNumber;


	//get own port number
	udpReceive.StartUp(portNum);
	udpSend.StartUp(portNum);

	//give names to game
	std::vector<std::string> names;
	for (const auto& i : playerData)
		names.push_back(i.second.portName);

	Game::InitPlayer(names);

	//keep receiving and send data
	std::thread receiveThread
	(std::bind(&NetworkManager::Receive, this));

	//only one thread needed due to broadcast
	std::thread sendThread
	(std::bind(&NetworkManager::Send, this));

	//thread for misc 
	std::thread idleThread
	(std::bind(&NetworkManager::Idle, this));

	receiveThread.join();
	sendThread.join();
	idleThread.join();

}

void NetworkManager::Idle()
{
	while (1)
	{
		//check states of players for transition to gameplay
		switch (GameState::GetCurrentState())
		{
		case  GameState::State::STATE_LOBBY:
		{
			const auto& playerName = NetworkManager::GetPlayerData();
			int connectCount = 0;
			for (const auto& p : playerName)
			{
				if (p.second.connected)
					connectCount++;
			}
			if (connectCount >= START_PLAYER)
				GameState::SetState(GameState::State::STATE_GAMEPLAY);
		}
		break;
		case  GameState::State::STATE_GAMEPLAY:
		{
			const auto& playerName = NetworkManager::GetPlayerData();
			int deadCount = 0;
			int connectCount = 0;
			for (const auto& p : playerName)
			{
				if (p.second.connected)
					connectCount++;

				if (p.second.connected && !p.second.alive)
					deadCount++;
			}
			//one winner left
			if (deadCount == connectCount-1)
				GameState::SetState(GameState::State::STATE_RESULTS);
		}
		break;
		}

	}

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
		(clientPlayer);


		//cannot find own player gameobject , don't send
		if (iter == GameObjectManager::GameObjectList.end())continue;

		//collate player data from gameobject
		playerData[0].score = iter->second->score;

		//placeholder
		MoveType type{ MoveType::MOVE_DOWN };
		//send player data
		Packet packet
		{ clientPlayer.c_str(),
			type,playerData[0],iter->second->translate };


		//check if other player gameobject is alive
		mutex.lock();
		for (auto& i : playerData)
		{
			if (i.second.alive)
			{
				const auto& iter = GameObjectManager::GameObjectList.find
				(i.second.portName);
				if (iter == GameObjectManager::GameObjectList.end()) break;
				if (i.second.connected && !iter->second->enabled)
				{

					strcpy(&packet.actionName[0], iter->first.c_str());
					packet.actionLength = static_cast<int>(iter->first.size());
					packet.moveType = MoveType::KILL;
					i.second.alive = false;
				}
			}
		}
		mutex.unlock();



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

	std::string temp
	{ packet.hostName,packet.hostName + packet.hostNameLength };
	mutex.lock();
	for (auto& i : playerData)
	{

		//received an active player
		if (i.second.portName == playerData[0].portName ||
			i.second.portName == packet.hostName)
			i.second.connected = true;

		if (i.second.portName == packet.hostName)
		{
			//temp - fix later - alive state
			bool tempAlive = i.second.alive;
			i.second = packet.playerData;
			i.second.alive = tempAlive;
		}

		//check if killed
		if (packet.moveType == MoveType::KILL)
		{
			std::string action
			{ packet.actionName,(packet.actionName) + packet.actionLength };
			if (i.second.alive && i.second.portName == action)
			{
				i.second.alive = false;
				const auto& iter = GameObjectManager::GameObjectList.find(action);
				iter->second->enabled = false;
				std::cout << "killed" << std::endl;
				break;
			}


		}

		if (i.second.portName != packet.hostName)
			i.second.connectionTimer += DeltaTime::GetDeltaTime();
	}
	mutex.unlock();
	if (GameObjectManager::GameObjectList.empty() ||
		playerData[0].portName == packet.hostName)
	{
		return;
	}





	const auto& iter = GameObjectManager::GameObjectList.find(temp);

	//cannot find player from gameobject container
	if (iter == GameObjectManager::GameObjectList.end())
		return;

	//update player position
	const auto& player = iter->second;

	player->score = packet.playerData.score;
	player->translate = packet.position;
}

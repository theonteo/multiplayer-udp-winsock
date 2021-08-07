/*****************************************************************************/
/*!
\file NetworkManager.cpp

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
#include "Window.h"
#include "CommonValues.h"

NetworkManager::NetworkManager()
{
	// Perform WinSock StartUp initialization
	WSAData wsaData{};
	SecureZeroMemory(&wsaData, sizeof(wsaData));
	int errorCode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	if (errorCode != NO_ERROR)
	{
		throw exceptionHandler("WSAStartup() failed.", errorCode);
	}
}

NetworkManager::~NetworkManager()
{
	if (clientSocket != INVALID_SOCKET)
	{
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
	}

	// WinSock cleanup
	WSACleanup();
}

const NetworkManager::PlayerArray& NetworkManager::GetPlayerData() const
{
	return players;
}

void NetworkManager::Init(char** argv)
{
	// Save all of the given hostname:port pairs
	localSocketAddr = SocketAddress{ argv[1] };
	for (size_t i = 1; i < MAX_PLAYER; ++i)
	{
		playerAddressMap.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(std::string{ argv[1 + i] }),
			std::forward_as_tuple(nullptr));
	}

	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (clientSocket == INVALID_SOCKET)
	{
		WSACleanup();
		throw
			exceptionHandler(
				"socket() failed.",
				static_cast<int>(clientSocket));
	}

	// Bind socket
	int errorCode =
		bind(clientSocket,
			&localSocketAddr.sockAddr,
			static_cast<int>(localSocketAddr.addrLen));

	if (errorCode != NO_ERROR)
	{
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
		WSACleanup();
		throw exceptionHandler("bind() failed.", errorCode);
	}

	// remove this
	Game::InitPlayer(0);
}

void NetworkManager::ConnectToPeers()
{
	for (const auto& playerAddress : playerAddressMap)
	{
		ConnectionPacket conPack;

		conPack.HtoN();

		// Send a connection request to each of the other players
		sendto(
			clientSocket,
			reinterpret_cast<char*>(&conPack),
			sizeof(ConnectionPacket),
			0,
			&playerAddress.first.sockAddr,
			sizeof(playerAddress.first.sockAddr));
	}

	// Wait for a reply with a timeout condition
	{
		// Wait for a timeout / acknowledgement packet
		std::unique_lock<std::mutex> timeoutLock{ timeoutMutex };

		bool receivedReply =
			timeoutCondition.wait_for(
				timeoutLock,
				std::chrono::seconds(TIMEOUT),
				[&]() { return receivedConnectionReply; });

		if(!receivedReply)
		{
			// Assume there is no existing "session"
			// Start own "session"
			localPlayerID = 0;
			players[0].hasPreviouslyConnnected = true;
			players[0].isConnected = true;
			Game::InitPlayer(localPlayerID);
		}
	}
}

//void NetworkManager::Idle()
//{
//	//while (1)
//	//{
//	//	//check states of players for transition to gameplay
//	//	switch (GameState::GetCurrentState())
//	//	{
//	//	case  GameState::State::STATE_LOBBY:
//	//	{
//	//		const auto& playerName = NetworkManager::GetPlayerData();
//	//		int connectCount = 0;
//	//		for (const auto& p : playerName)
//	//		{
//	//			if (p.connected)
//	//				connectCount++;
//	//		}
//	//		if (connectCount >= START_PLAYER)
//	//			GameState::SetState(GameState::State::STATE_GAMEPLAY);
//	//	}
//	//	break;
//	//	case  GameState::State::STATE_GAMEPLAY:
//	//	{
//	//		const auto& playerName = NetworkManager::GetPlayerData();
//	//		int deadCount = 0;
//	//		int connectCount = 0;
//	//		for (const auto& p : playerName)
//	//		{
//	//			if (p.connected)
//	//				connectCount++;
//	//
//	//			if (p.connected && !p.alive)
//	//				deadCount++;
//	//		}
//	//		//one winner left
//	//		if (deadCount == connectCount-1)
//	//			GameState::SetState(GameState::State::STATE_RESULTS);
//	//	}
//	//	break;
//	//	}
//	//
//	//}
//
//}

void NetworkManager::Send()
{
	bool isWPressed = Window::getKeyTriggered(GLFW_KEY_W);
	bool isAPressed = Window::getKeyTriggered(GLFW_KEY_A);
	bool isSPressed = Window::getKeyTriggered(GLFW_KEY_S);
	bool isDPressed = Window::getKeyTriggered(GLFW_KEY_D);
	bool isWReleased = Window::getKeyReleased(GLFW_KEY_W);
	bool isAReleased = Window::getKeyReleased(GLFW_KEY_A);
	bool isSReleased = Window::getKeyReleased(GLFW_KEY_S);
	bool isDReleased = Window::getKeyReleased(GLFW_KEY_D);

	if (isWPressed || isAPressed || isSPressed || isDPressed ||
		isWReleased || isAReleased || isSReleased || isDReleased)
	{
		// Send a data packet to all other players
		DataPacket dataPacket;

		dataPacket.moveInfo |=
			Window::getKey(GLFW_KEY_W) *
			static_cast<unsigned char>(MoveType::MOVE_UP);

		dataPacket.moveInfo |=
			Window::getKey(GLFW_KEY_A) *
			static_cast<unsigned char>(MoveType::MOVE_LEFT);

		dataPacket.moveInfo |=
			Window::getKey(GLFW_KEY_S) *
			static_cast<unsigned char>(MoveType::MOVE_DOWN);

		dataPacket.moveInfo |=
			Window::getKey(GLFW_KEY_D) *
			static_cast<unsigned char>(MoveType::MOVE_RIGHT);

		// Make sure that this client has a valid assigned ID
		if (localPlayerID == INVALID_ID)
		{
			return;
		}

		auto goIter =
			GameObjectManager::GameObjectList.find(
				"Player " + std::to_string(localPlayerID + 1));

		dataPacket.position = goIter->second->translate;

		dataPacket.HtoN();

		for (const auto& playerAddress : playerAddressMap)
		{
			if (playerAddress.second &&
				playerAddress.second->isConnected)
			{
				// Send a connection notification to the other players
				sendto(
					clientSocket,
					reinterpret_cast<char*>(&dataPacket),
					sizeof(dataPacket),
					0,
					&playerAddress.first.sockAddr,
					sizeof(playerAddress.first.sockAddr));
			}
		}
	}

	//const auto& playerName = NetworkManager::GetPlayerData();
	//
	////player container is empty ,don't send
	//if (playerName.empty()) return;
	//
	////placeholder testing - change to proper packet next time
	//const auto& iter =
	//	GameObjectManager::GameObjectList.find(clientPlayer);
	//
	//
	////cannot find own player gameobject , don't send
	//if (iter == GameObjectManager::GameObjectList.end()) return;
	//
	////collate player data from gameobject
	//auto& pl = playerData.find(clientPlayer)->second;
	//pl.score = iter->second->score;
	//
	////placeholder
	//MoveType type{ MoveType::MOVE_DOWN };
	////send player data
	//Packet packet
	//{
	//	clientPlayer.c_str(),
	//	type,pl,iter->second->translate
	//};
	//
	//
	////check if other player gameobject is alive
	//mutex.lock();
	//for (auto& i : playerData)
	//{
	//	if (i.second.alive)
	//	{
	//		const auto& iter = GameObjectManager::GameObjectList.find
	//		(i.second.portName);
	//		if (iter == GameObjectManager::GameObjectList.end()) break;
	//		if (i.second.connected && !iter->second->enabled)
	//		{
	//			strcpy(&packet.actionName[0], iter->first.c_str());
	//			packet.actionLength = static_cast<int>(iter->first.size());
	//			packet.moveType = MoveType::KILL;
	//			i.second.alive = false;
	//		}
	//	}
	//}
	//mutex.unlock();
	//
	//
	//
	////send player info - for testing
	//udp.SendBroadcast(packet);
}

void NetworkManager::Receive()
{
	while (true)
	{
		//keep receiving packet then process them accordingly
		char buffer[MAX_PACKET_SIZE];
		int sourceAddrSize = sizeof(sockaddr);
		sockaddr sourceAddr;

		int bytesReceived =
			recvfrom(
				clientSocket,
				buffer,
				MAX_PACKET_SIZE,
				0,
				&sourceAddr,
				&sourceAddrSize);

		if (bytesReceived != SOCKET_ERROR)
		{
			//unpack and give data to gameplay containers(player pos etc)
			UnpackPacket(buffer, SocketAddress{ sourceAddr });
		}
	}
}

void NetworkManager::UnpackPacket(
	char* buffer, const SocketAddress& sourceAddr)
{
	const Packet* packet = reinterpret_cast<const Packet*>(buffer);

	if (packet->packetType == PacketType::CONNECTION_REQUEST)
	{
		ProcessConnectionRequest(sourceAddr);
	}
	else if (packet->packetType == PacketType::CONNECTION_REPLY)
	{
		ProcessConnectionReply(
			*reinterpret_cast<ConnectionReply*>(buffer), sourceAddr);
	}
	else if (packet->packetType == PacketType::CONNECTION_CONFIRMATION)
	{
		ProcessConnectionConfirmation(
			*reinterpret_cast<ConnectionConfirmation*>(buffer), sourceAddr);
	}
	else if (packet->packetType == PacketType::CONNECTION_NOTIFICATION)
	{
		ProcessConnectionNotification(
			*reinterpret_cast<ConnectionNotification*>(buffer),
			sourceAddr);
	}
	else if (packet->packetType == PacketType::DATA_PACKET)
	{
		ProcessDataPacket(
			*reinterpret_cast<DataPacket*>(buffer), sourceAddr);
	}

	////same person - return
	//
	//std::string temp
	//{ packet.hostName,packet.hostName + packet.hostNameLength };
	//
	//
	//
	//mutex.lock();
	//auto& pl = playerData.find(clientPlayer)->second;
	//for (auto& i : playerData)
	//{
	//	//received an active player
	//	if (i.second.portName == pl.portName ||
	//		i.second.portName == packet.hostName)
	//		i.second.connected = true;
	//
	//	if (i.second.portName == packet.hostName)
	//	{
	//		//temp - fix later - alive state
	//		bool tempAlive = i.second.alive;
	//		i.second = packet.playerData;
	//		i.second.alive = tempAlive;
	//	}
	//
	//	//check if killed
	//	if (packet.moveType == MoveType::KILL)
	//	{
	//		std::string action
	//		{ packet.actionName,(packet.actionName) + packet.actionLength };
	//		if (i.second.alive && i.second.portName == action)
	//		{
	//			i.second.alive = false;
	//			const auto& iter = GameObjectManager::GameObjectList.find(action);
	//			iter->second->enabled = false;
	//			std::cout << "killed" << std::endl;
	//			break;
	//		}
	//
	//
	//	}
	//
	//	if (i.second.portName != packet.hostName)
	//		i.second.connectionTimer += DeltaTime::GetDeltaTime();
	//}
	//mutex.unlock();
	//if (GameObjectManager::GameObjectList.empty() ||
	//	pl.portName == packet.hostName)
	//{
	//	return;
	//}
	//
	//const auto& iter = GameObjectManager::GameObjectList.find(temp);
	//
	////cannot find player from gameobject container
	//if (iter == GameObjectManager::GameObjectList.end())
	//	return;
	//
	////update player position
	//const auto& player = iter->second;
	//
	//player->score = packet.playerData.score;
	//player->translate = packet.position;
}

void NetworkManager::ProcessConnectionRequest(const SocketAddress& sourceAddr)
{
	// Check if this client is the current host
	// Only the host need to reply
	if (localPlayerID == 0)	// Changer later to "== hostID"
	{
		const auto& iter = playerAddressMap.find(sourceAddr);
		if (iter != playerAddressMap.end())
		{
			// Check if client requesting to join has previously connected
			if (iter->second)
			{
				// Reconnect the player
				// Set isConnected to true
				// Reply with a reconnection confirmation of some sort
				// Maybe send the entire game data for the client to "catch up"
			}
			else
			{
				// Find an empty player slot
				unsigned short assignedID = 0;
				for (unsigned short i = 0; i < MAX_PLAYER; ++i)
				{
					if (!players[i].hasPreviouslyConnnected)
					{
						assignedID = i;
						break;
					}
				}

				// Send a connection reply to the player that requested to join
				ConnectionReply replyPacket;

				const sockaddr_in* sockAddrPtr =
					reinterpret_cast<const sockaddr_in*>(
						&localSocketAddr.sockAddr);

				replyPacket.ports[0] = ntohs(sockAddrPtr->sin_port);
				replyPacket.ips[0] = sockAddrPtr->sin_addr;
				replyPacket.playerIndices[0] = 0;

				int counter = 1;
				for (const auto& playerAddress : playerAddressMap)
				{
					if (playerAddress.first != sourceAddr)
					{
						sockAddrPtr =
							reinterpret_cast<const sockaddr_in*>(
								&playerAddress.first.sockAddr);

						replyPacket.assignedID = assignedID;

						replyPacket.playerIndices[counter] =
							playerAddress.second == nullptr ?
							INVALID_ID :
							static_cast<unsigned short>(
								playerAddress.second - players.data());

						replyPacket.ports[counter] =
							ntohs(sockAddrPtr->sin_port);

						replyPacket.ips[counter] = sockAddrPtr->sin_addr;


						++counter;
					}
				}

				replyPacket.HtoN();

				sendto(
					clientSocket,
					reinterpret_cast<char*>(&replyPacket),
					sizeof(ConnectionReply),
					0,
					&sourceAddr.sockAddr,
					sizeof(sourceAddr.sockAddr));
			}
		}
	}
}

void NetworkManager::ProcessConnectionReply(
	ConnectionReply& replyPacket, const SocketAddress& sourceAddr)
{
	// Check if this client has already started its own session
	if (localPlayerID == INVALID_ID)
	{
		replyPacket.NtoH();

		// Notify lock
		receivedConnectionReply = true;
		timeoutCondition.notify_one();

		// Save this client's assigned ID
		localPlayerID = replyPacket.assignedID;
		Game::InitPlayer(localPlayerID);
		players[localPlayerID].hasPreviouslyConnnected = true;
		players[localPlayerID].isConnected = true;

		for (int i = 0; i < MAX_PEER; ++i)
		{
			if (replyPacket.playerIndices[i] != INVALID_ID)
			{
				sockaddr_in sockAddr;
				sockAddr.sin_addr = replyPacket.ips[i];
				sockAddr.sin_port = htons(replyPacket.ports[i]);
				SocketAddress peerAddr
				{
					*reinterpret_cast<sockaddr*>(&sockAddr)
				};

				playerAddressMap[peerAddr] =
					&players[replyPacket.playerIndices[i]];

				playerAddressMap[peerAddr]->hasPreviouslyConnnected = true;
				playerAddressMap[peerAddr]->isConnected = true;
			}
		}

		// Send connection confirmation
		ConnectionConfirmation conConfirm;
		conConfirm.assignedID = replyPacket.assignedID;
		conConfirm.HtoN();

		sendto(
			clientSocket,
			reinterpret_cast<char*>(&conConfirm),
			sizeof(ConnectionConfirmation),
			0,
			&sourceAddr.sockAddr,
			sizeof(sourceAddr.sockAddr));

		if (GameState::GetCurrentState() == GameState::State::STATE_LOBBY)
		{
			int connectCount = 0;
			for (const auto& p : players)
			{
				if (p.isConnected)
					connectCount++;
			}
			if (connectCount >= START_PLAYER)
				GameState::SetState(GameState::State::STATE_GAMEPLAY);
		}
	}
}

void NetworkManager::ProcessConnectionConfirmation(
	ConnectionConfirmation& conConfirm,
	const SocketAddress& sourceAddr)
{
	conConfirm.NtoH();

	auto iter = playerAddressMap.find(sourceAddr);
	if (iter != playerAddressMap.end())
	{
		players[conConfirm.assignedID].hasPreviouslyConnnected = true;
		players[conConfirm.assignedID].isConnected = true;
		iter->second = &players[conConfirm.assignedID];

		// Send a connection notification to the other players
		const sockaddr_in* sockAddrPtr =
			reinterpret_cast<const sockaddr_in*>(
				&sourceAddr.sockAddr);

		ConnectionNotification conNotif;
		conNotif.joiningID = conConfirm.assignedID;
		conNotif.ip = sockAddrPtr->sin_addr;
		conNotif.port = sockAddrPtr->sin_port;
		conNotif.HtoN();

		for (const auto& playerAddress : playerAddressMap)
		{
			if (playerAddress.second &&
				playerAddress.first != sourceAddr)
			{
				// Send a connection notification to the other players
				sendto(
					clientSocket,
					reinterpret_cast<char*>(&conNotif),
					sizeof(conNotif),
					0,
					&playerAddress.first.sockAddr,
					sizeof(playerAddress.first.sockAddr));
			}
		}

		if (GameState::GetCurrentState() == GameState::State::STATE_LOBBY)
		{
			int connectCount = 0;
			for (const auto& p : players)
			{
				if (p.isConnected)
					connectCount++;
			}
			if (connectCount >= START_PLAYER)
				GameState::SetState(GameState::State::STATE_GAMEPLAY);
		}
	}
}

void NetworkManager::ProcessConnectionNotification(
	ConnectionNotification& conNotif, const SocketAddress& sourceAddr)
{
	conNotif.NtoH();

	auto iter = playerAddressMap.find(sourceAddr);
	if (iter != playerAddressMap.end())
	{
		players[conNotif.joiningID].hasPreviouslyConnnected = true;
		players[conNotif.joiningID].isConnected = true;
		iter->second = &players[conNotif.joiningID];

		if (GameState::GetCurrentState() == GameState::State::STATE_LOBBY)
		{
			int connectCount = 0;
			for (const auto& p : players)
			{
				if (p.isConnected)
					connectCount++;
			}
			if (connectCount >= START_PLAYER)
				GameState::SetState(GameState::State::STATE_GAMEPLAY);
		}
	}
}

void NetworkManager::ProcessDataPacket(
	DataPacket& dataPacket, const SocketAddress& sourceAddr)
{
	dataPacket.NtoH();

	auto iter = playerAddressMap.find(sourceAddr);
	if (iter != playerAddressMap.end())
	{
		auto goIter =
			GameObjectManager::GameObjectList.find(
				"Player " + std::to_string((iter->second - &players[0]) + 1));
		
		//cannot find player from gameobject container
		if (goIter == GameObjectManager::GameObjectList.end())
			return;
		
		//update player position
		const auto& player = goIter->second;
		
		player->translate = dataPacket.position;
		player->direction = dataPacket.moveInfo;
	}
}

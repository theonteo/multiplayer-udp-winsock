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
#include "UIManager.h"
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
	ShutDown();
}

void NetworkManager::ShutDown()
{
	if (!isShuttingDown)
	{
		isShuttingDown = true;

		// Send shutdown notification to other clients
		for (const auto& playerAddress : playerAddressMap)
		{
			DisconnectNotification disconnectNotif;

			disconnectNotif.HtoN();

			// Send a connection request to each of the other players
			sendto(
				clientSocket,
				reinterpret_cast<char*>(&disconnectNotif),
				sizeof(disconnectNotif),
				0,
				&playerAddress.first.sockAddr,
				sizeof(playerAddress.first.sockAddr));
		}

		if (clientSocket != INVALID_SOCKET)
		{
			closesocket(clientSocket);
			clientSocket = INVALID_SOCKET;
		}

		// WinSock cleanup
		WSACleanup();
	}
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
	UIManager::InitPlayer(0);
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
			players[0].isConnected = true;
			connectedPlayers = 1;
			hostID = 0;
			Game::InitPlayer(localPlayerID);
			UIManager::InitPlayer(localPlayerID);
		}
	}
}

void NetworkManager::Send()
{
	if (localPlayerID == INVALID_ID ||
		!players[localPlayerID].isConnected)
	{
		return;
	}
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

		++players[localPlayerID].latestPacket;
		dataPacket.packetNum = players[localPlayerID].latestPacket;

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

	{
		std::lock_guard<std::mutex> lock(lockstepMutex);
		if (lockstepMode)
		{
			if (!startedLockstep)
			{
				++hashedDataReceived;
				++lockstepDataReceived;
			}

			// Sending of hashed data
			SendHashedPacket();

			// Wait for everyone to reply / timeout
			{
				std::unique_lock<std::mutex> timeoutLock{ timeoutMutex };

				timeoutCondition.wait_for(
					timeoutLock,
					std::chrono::milliseconds(TIMEOUT_LOCKSTEP),
					[&]() { return hashedDataReceived == connectedPlayers; });
			}

			// Send back the actual action to everyoone
			SendLockstepPacket();

			// Wait for everyone's actual action
			{
				std::unique_lock<std::mutex> timeoutLock{ timeoutMutex };

				timeoutCondition.wait_for(
					timeoutLock,
					std::chrono::milliseconds(TIMEOUT_LOCKSTEP),
					[&]() { return lockstepDataReceived == connectedPlayers; });
			}

			// Process all of the data
			for (size_t i = 0; i < MAX_PLAYER; ++i)
			{
				if (!hashedData[i].first || !lockstepData[i].first)
				{
					continue;
				}

				size_t tempHashedData =
					std::hash<LockstepDataPacket>()(lockstepData[i].second);

				if (tempHashedData != hashedData[i].second.hashedData)
				{
					continue;
				}

				unsigned short collidingID =
					lockstepData[i].second.GetCollidingID();

				if (collidingID == INVALID_ID)
				{
					continue;
				}

				if (collidingID < 1000)
				{
					++players[i].score;

					auto& otherGO =
						GameObjectManager::GameObjectList.find(
							"item " + std::to_string(collidingID))->second;

					otherGO->enabled = false;
				}
				else
				{
					players[i].score += 3;
					collidingID -= 1000;

					auto& otherGO =
						GameObjectManager::GameObjectList.find(
							"Player " + std::to_string(collidingID))->second;

					otherGO->enabled = false;

					int deadCount = 0;

					deadCount +=
						!GameObjectManager::GameObjectList.find(
							"Player 1")->second->enabled;

					deadCount +=
						!GameObjectManager::GameObjectList.find(
							"Player 2")->second->enabled;

					deadCount +=
						!GameObjectManager::GameObjectList.find(
							"Player 3")->second->enabled;

					deadCount +=
						!GameObjectManager::GameObjectList.find(
							"Player 4")->second->enabled;

					//one winner left
					if (deadCount >= MAX_PEER)
					{
						GameState::SetState(GameState::State::STATE_RESULTS);
					}
				}

				auto& playerGO =
					GameObjectManager::GameObjectList.find(
						"Player " + std::to_string(i + 1))->second;

				playerGO->score = players[i].score;
			}

			// Reset
			for (size_t i = 0; i < MAX_PLAYER; ++i)
			{
				hashedData[i].first = false;
				lockstepData[i].first = false;
			}
			lockstepData[localPlayerID].second.SetCollidingID(INVALID_ID);

			hashedData[localPlayerID].second.hashedData =
				std::hash<LockstepDataPacket>()(
					lockstepData[localPlayerID].second);

			hashedDataReceived = 0;
			lockstepDataReceived = 0;

			--lockstepMode;
			startedLockstep = false;
		}
	}
}

void NetworkManager::Receive()
{
	while (!isShuttingDown)
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

void NetworkManager::StartLockstep(unsigned short collidingID)
{
	lockstepMode = true;
	{
		std::lock_guard<std::mutex> lock(lockstepMutex);
		startedLockstep = true;
	}
	lockstepData[localPlayerID].first = true;
	lockstepData[localPlayerID].second.SetCollidingID(collidingID);

	hashedData[localPlayerID].first = true;
	hashedData[localPlayerID].second.hashedData =
		std::hash<LockstepDataPacket>()(
			lockstepData[localPlayerID].second);

	++hashedDataReceived;
	++lockstepDataReceived;


	InitiateLockstepPacket initLockstepPack{};

	for (const auto& playerAddress : playerAddressMap)
	{
		if (playerAddress.second)
		{
			// Send a connection notification to the other players
			sendto(
				clientSocket,
				reinterpret_cast<char*>(&initLockstepPack),
				sizeof(initLockstepPack),
				0,
				&playerAddress.first.sockAddr,
				sizeof(playerAddress.first.sockAddr));
		}
	}
}

void NetworkManager::SendHashedPacket()
{
	HashedDataPacket data = hashedData[localPlayerID].second;
	data.HtoN();

	for (const auto& playerAddress : playerAddressMap)
	{
		if (playerAddress.second &&
			playerAddress.second->isConnected)
		{
			// Send a hashed packet to the other players
			sendto(
				clientSocket,
				reinterpret_cast<char*>(&data),
				sizeof(data),
				0,
				&playerAddress.first.sockAddr,
				sizeof(playerAddress.first.sockAddr));
		}
	}
}

void NetworkManager::SendLockstepPacket()
{
	LockstepDataPacket data = lockstepData[localPlayerID].second;
	data.HtoN();

	for (const auto& playerAddress : playerAddressMap)
	{
		if (playerAddress.second &&
			playerAddress.second->isConnected)
		{
			// Send a hashed packet to the other players
			sendto(
				clientSocket,
				reinterpret_cast<char*>(&data),
				sizeof(data),
				0,
				&playerAddress.first.sockAddr,
				sizeof(playerAddress.first.sockAddr));
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
			*reinterpret_cast<ConnectionNotification*>(buffer));
	}
	else if (packet->packetType == PacketType::RECONNECTION_REPLY)
	{
		ProcessReconnectionReply(
			*reinterpret_cast<ReconnectionReply*>(buffer), sourceAddr);
	}
	else if (packet->packetType == PacketType::DISCONNECT_NOTIFICATION)
	{
		ProcessDisconnectNotification(sourceAddr);
	}
	

	else if (GameState::GetCurrentState() == GameState::State::STATE_GAMEPLAY)
	{
		if (packet->packetType == PacketType::DATA_PACKET)
		{
			ProcessDataPacket(
				*reinterpret_cast<DataPacket*>(buffer), sourceAddr);
		}
		else if (packet->packetType == PacketType::INITIATE_LOCKSTEP)
		{
			ProcessInitiateLockstepPacket();
		}
		else if (packet->packetType == PacketType::LOCKSTEP_DATA)
		{
			ProcessLockstepDataPacket(
				*reinterpret_cast<LockstepDataPacket*>(buffer), sourceAddr);
		}
		else if (packet->packetType == PacketType::HASHED_DATA)
		{
			ProcessHashedDataPacket(
				*reinterpret_cast<HashedDataPacket*>(buffer), sourceAddr);
		}
	}
}

void NetworkManager::ProcessConnectionRequest(const SocketAddress& sourceAddr)
{
	// Check if this client is the current host
	// Only the host need to reply
	if (localPlayerID == hostID)
	{
		const auto& iter = playerAddressMap.find(sourceAddr);
		if (iter != playerAddressMap.end())
		{
			// Check if client requesting to join has previously connected
			if (iter->second)
			{
				// Reconnect the player
				unsigned short assignedID = iter->second - &players[0];

				ReconnectionReply reconPacket;

				GenerateConnectionReply(
					*reinterpret_cast<ConnectionReply*>(&reconPacket),
					sourceAddr,
					assignedID);

				GenerateReconnectionReply(reconPacket);

				reconPacket.HtoN();

				sendto(
					clientSocket,
					reinterpret_cast<char*>(&reconPacket),
					sizeof(reconPacket),
					0,
					&sourceAddr.sockAddr,
					sizeof(sourceAddr.sockAddr));
			}
			else if(GameState::GetCurrentState() ==
				    GameState::State::STATE_LOBBY)
			{
				// Find an empty player slot
				unsigned short assignedID = 0;
				for (unsigned short i = 0; i < MAX_PLAYER; ++i)
				{
					if (!players[i].isConnected)
					{
						assignedID = i;
						break;
					}
				}

				// Send a connection reply to the player that requested to join
				ConnectionReply replyPacket;
				GenerateConnectionReply(replyPacket, sourceAddr, assignedID);

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
		hostID = replyPacket.hostID;
		Game::InitPlayer(localPlayerID);
		UIManager::InitPlayer(localPlayerID);
		players[localPlayerID].isConnected = true;
		++connectedPlayers;

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

				playerAddressMap[peerAddr]->isConnected = true;
				++connectedPlayers;
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
		players[conConfirm.assignedID].isConnected = true;
		++connectedPlayers;
		iter->second = &players[conConfirm.assignedID];

		// Send a connection notification to the other players
		const sockaddr_in* sockAddrPtr =
			reinterpret_cast<const sockaddr_in*>(
				&sourceAddr.sockAddr);

		ConnectionNotification conNotif;
		conNotif.joiningID = conConfirm.assignedID;
		conNotif.ip = sockAddrPtr->sin_addr;
		conNotif.port = ntohs(sockAddrPtr->sin_port);
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

void NetworkManager::ProcessConnectionNotification(ConnectionNotification& conNotif)
{
	conNotif.NtoH();

	sockaddr_in sockAddr;
	sockAddr.sin_addr = conNotif.ip;
	sockAddr.sin_port = htons(conNotif.port);

	auto iter = playerAddressMap.find(
		SocketAddress{*reinterpret_cast<sockaddr*>(&sockAddr)});

	if (iter != playerAddressMap.end())
	{
		players[conNotif.joiningID].isConnected = true;
		++connectedPlayers;
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
		// Ensure the we only process the latest packets
		// Ignore outdated packets
		if (dataPacket.packetNum > iter->second->latestPacket)
		{
			iter->second->latestPacket = dataPacket.packetNum;

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
}

void NetworkManager::ProcessInitiateLockstepPacket()
{
	std::lock_guard<std::mutex> lock(lockstepMutex);
	if (!startedLockstep)
	{
		++lockstepMode;
	}
}

void NetworkManager::ProcessLockstepDataPacket(
	LockstepDataPacket& dataPacket, const SocketAddress& sourceAddr)
{
	dataPacket.NtoH();

	auto iter = playerAddressMap.find(sourceAddr);
	if (iter != playerAddressMap.end())
	{
		size_t senderIndex = iter->second - &players[0];

		lockstepData[senderIndex].first = true;
		lockstepData[senderIndex].second = dataPacket;

		++lockstepDataReceived;

		if (lockstepDataReceived == connectedPlayers)
		{
			timeoutCondition.notify_one();
		}
	}
}

void NetworkManager::ProcessHashedDataPacket(
	HashedDataPacket& dataPacket, const SocketAddress& sourceAddr)
{
	dataPacket.NtoH();

	auto iter = playerAddressMap.find(sourceAddr);
	if (iter != playerAddressMap.end())
	{
		size_t senderIndex = iter->second - &players[0];

		hashedData[senderIndex].first = true;
		hashedData[senderIndex].second = dataPacket;

		++hashedDataReceived;

		if (hashedDataReceived == connectedPlayers)
		{
			timeoutCondition.notify_one();
		}
	}
}

void NetworkManager::ProcessDisconnectNotification(const SocketAddress& sourceAddr)
{
	auto iter = playerAddressMap.find(sourceAddr);

	if (iter != playerAddressMap.end() && iter->second)
	{
		iter->second->isConnected = false;
		--connectedPlayers;

		if (iter->second - &players[0] == hostID)
		{
			for (int i = 0; i < MAX_PLAYER; ++i)
			{
				if (players[i].isConnected)
				{
					hostID = i;
					break;
				}
			}
		}

		if (GameState::GetCurrentState() ==
			GameState::State::STATE_LOBBY)
		{
			playerAddressMap[sourceAddr] = nullptr;
		}
	}
}

void NetworkManager::ProcessReconnectionReply(ReconnectionReply& replyPacket, const SocketAddress& sourceAddr)
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
		hostID = replyPacket.hostID;
		Game::InitPlayer(localPlayerID);
		UIManager::InitPlayer(localPlayerID);
		players[localPlayerID].isConnected = true;
		++connectedPlayers;

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

				playerAddressMap[peerAddr]->isConnected = true;
				++connectedPlayers;
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

		Game::SetGameTime(replyPacket.gameTime);

		for (int i = 0; i < MAX_FOOD; ++i)
		{
			auto& foodGO =
				GameObjectManager::GameObjectList.find(
					"item " + std::to_string(i))->second;
			
			foodGO->enabled =
				replyPacket.isEnabled[i / 8] & (1 << (i % 8));
		}

		for (int i = 1; i <= MAX_PLAYER; ++i)
		{
			const auto& playerGO =
				GameObjectManager::GameObjectList.find(
					"Player " + std::to_string(i))->second;

			int index = MAX_FOOD + i - 1;

			playerGO->enabled =
				replyPacket.isEnabled[index / 8] & (1 << (index % 8));

			players[i - 1].score = replyPacket.scores[i - 1];
			players[i - 1].isConnected = replyPacket.isConnected & (1 << (i - 1));
			players[i - 1].latestPacket = replyPacket.latestPackets[i - 1];
			playerGO->score = replyPacket.scores[i - 1];
			playerGO->translate = replyPacket.positions[i - 1];
			playerGO->direction = replyPacket.moveInfos[i - 1];
		}

		players[localPlayerID].isConnected = true;
		connectedPlayers = 0;
		for (int i = 0; i < MAX_PLAYER; ++i)
		{
			if (players[i].isConnected)
			{
				++connectedPlayers;
			}
		}
		GameState::SetState(GameState::State::STATE_GAMEPLAY);
	}
}

void NetworkManager::GenerateConnectionReply(
	ConnectionReply& replyPacket,
	const SocketAddress& sourceAddr,
	unsigned short assignedID)
{
	const sockaddr_in* sockAddrPtr =
		reinterpret_cast<const sockaddr_in*>(
			&localSocketAddr.sockAddr);

	replyPacket.ports[0] = ntohs(sockAddrPtr->sin_port);
	replyPacket.ips[0] = sockAddrPtr->sin_addr;
	replyPacket.playerIndices[0] = localPlayerID;

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
}

void NetworkManager::GenerateReconnectionReply(ReconnectionReply& replyPacket)
{
	replyPacket.gameTime = Game::GetGameTime();

	for (int i = 1; i <= MAX_PLAYER; ++i)
	{
		const auto& iter =
			GameObjectManager::GameObjectList.find(
				"Player " + std::to_string(i))->second;

		replyPacket.scores[i - 1] = iter->score;
		replyPacket.moveInfos[i - 1] = iter->direction;
		replyPacket.positions[i - 1] = iter->translate;
	}

	// Copy the enabled data
	std::bitset<MAX_FOOD + MAX_PLAYER> isEnabled;
	for (int i = 0; i < MAX_FOOD; ++i)
	{
		const auto& iter =
			GameObjectManager::GameObjectList.find(
				"item " + std::to_string(i))->second;

		isEnabled[i] = iter->enabled;
	}

	for (int i = 1; i <= MAX_PLAYER; ++i)
	{
		const auto& iter =
			GameObjectManager::GameObjectList.find(
				"Player " + std::to_string(i))->second;

		isEnabled[MAX_FOOD + i - 1] = iter->enabled;
	}

	for (int i = 0; i < ReconnectionReply::MAX_ENABLED; ++i)
	{
		int index = i * 8;

		for (int j = 0; j < 8; ++j)
		{
			if (index + j < MAX_FOOD + MAX_PLAYER)
			{
				replyPacket.isEnabled[i] |= (isEnabled[index + j] << j);
			}
		}
	}

	for (int i = 1; i <= MAX_PLAYER; ++i)
	{
		replyPacket.isConnected |= players[i - 1].isConnected << (i - 1);
		replyPacket.latestPackets[i - 1] = players[i - 1].latestPacket;
	}
}
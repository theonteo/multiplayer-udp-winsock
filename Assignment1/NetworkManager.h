/*****************************************************************************/
/*!
\file NetworkManager.h

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
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "Windows.h"
#include "ws2tcpip.h"

#pragma comment(lib, "ws2_32.lib")

#include <string>
#include <unordered_map>
#include <array>
#include <mutex>

#include "Player.h"
#include "SocketAddress.h"
#include "CommonValues.h"
#include "Packet.h"

class Player;

class NetworkManager
{
public:
	using PlayerArray = std::array<Player, MAX_PLAYER>;

private:
	static constexpr size_t TIMEOUT = 1;				// in seconds
	static constexpr size_t TIMEOUT_LOCKSTEP = 300;		// in milliseconds

	static constexpr unsigned short INVALID_ID =
		static_cast<unsigned short>(-1);

	SOCKET clientSocket = INVALID_SOCKET;

	std::unordered_map<SocketAddress, Player*> playerAddressMap;
	SocketAddress localSocketAddr;
	PlayerArray players;
	int connectedPlayers = 0;
	unsigned short localPlayerID = INVALID_ID;

	// To wait for timeout
	std::mutex timeoutMutex;
	std::condition_variable timeoutCondition;
	bool receivedConnectionReply = false;

	// Lockstep
	std::mutex lockstepMutex{};
	int lockstepMode = 0;
	bool startedLockstep = false;
	std::array<std::pair<bool, HashedDataPacket>, MAX_PLAYER> hashedData;
	int hashedDataReceived = 0;
	std::array<std::pair<bool, LockstepDataPacket>, MAX_PLAYER> lockstepData;
	int lockstepDataReceived = 0;

public:
	NetworkManager();
	~NetworkManager();

	const PlayerArray& GetPlayerData() const;

	void Init(char** argv);
	void ConnectToPeers();

	void Send();
	void Receive();

	void StartLockstep(unsigned short collidingID);
	void SendHashedPacket();
	void SendLockstepPacket();

	void UnpackPacket(
		char* buffer, const SocketAddress& sourceAddr);

	void ProcessConnectionRequest(const SocketAddress& sourceAddr);

	void ProcessConnectionReply(
		ConnectionReply& replyPacket, const SocketAddress& sourceAddr);

	void ProcessConnectionConfirmation(
		ConnectionConfirmation& conConfirm,
		const SocketAddress& sourceAddr);

	void ProcessConnectionNotification(ConnectionNotification& conNotif);

	void ProcessDataPacket(
		DataPacket& dataPacket, const SocketAddress& sourceAddr);

	void ProcessInitiateLockstepPacket();

	void ProcessLockstepDataPacket(
		LockstepDataPacket& dataPacket, const SocketAddress& sourceAddr);

	void ProcessHashedDataPacket(
		HashedDataPacket& dataPacket, const SocketAddress& sourceAddr);
};


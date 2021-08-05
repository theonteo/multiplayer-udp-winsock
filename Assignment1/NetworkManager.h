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
	static constexpr size_t TIMEOUT = 1;

	static constexpr unsigned short INVALID_ID =
		static_cast<unsigned short>(-1);

	SOCKET clientSocket = INVALID_SOCKET;

	std::unordered_map<SocketAddress, Player*> playerAddressMap;
	SocketAddress localSocketAddr;
	PlayerArray players;
	unsigned short localPlayerID = INVALID_ID;

	// To wait for timeout
	std::mutex timeoutMutex;
	std::condition_variable timeoutCondition;
	bool receivedConnectionReply = false;

public:
	NetworkManager();
	~NetworkManager();

	const PlayerArray& GetPlayerData() const;

	void Init(char** argv);
	void ConnectToPeers();

	void Send();
	void Receive();


	void UnpackPacket(
		char* buffer, const SocketAddress& sourceAddr);

	void ProcessConnectionRequest(const SocketAddress& sourceAddr);

	void ProcessConnectionReply(
		ConnectionReply& replyPacket, const SocketAddress& sourceAddr);

	void ProcessConnectionConfirmation(
		ConnectionConfirmation& conConfirm,
		const SocketAddress& sourceAddr);

	void ProcessConnectionNotification(
		ConnectionNotification& conNotif,
		const SocketAddress& sourceAddr);

	void ProcessDataPacket(
		DataPacket& dataPacket, const SocketAddress& sourceAddr);
};


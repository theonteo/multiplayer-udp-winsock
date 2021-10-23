/******************************************************************************/
/*!
\file NetworkingManager.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/
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
	static constexpr size_t TIMEOUT_LOCKSTEP = 500;		// in milliseconds

	static constexpr unsigned short INVALID_ID =
		static_cast<unsigned short>(-1);

	SOCKET clientSocket = INVALID_SOCKET;

	std::unordered_map<SocketAddress, Player*> playerAddressMap;
	SocketAddress localSocketAddr;
	PlayerArray players;
	int connectedPlayers = 0;
	unsigned short localPlayerID = INVALID_ID;
	unsigned short hostID = INVALID_ID;

	// To wait for timeout
	std::mutex timeoutMutex;
	std::condition_variable timeoutCondition;
	bool receivedConnectionReply = false;

	// Lockstep
	std::mutex lockstepMutex{};
	std::mutex dataMutex{};
	bool lockstepMode = false;
	bool startedLockstep = false;
	unsigned int lockstepCounter = 0;
	std::array<std::pair<bool, HashedDataPacket>, MAX_PLAYER> hashedData;
	int hashedDataReceived = 0;
	std::array<std::pair<bool, LockstepDataPacket>, MAX_PLAYER> lockstepData;
	int lockstepDataReceived = 0;

	//Shutdown
	bool isShuttingDown = false;

	//Pinging
	static constexpr float PING_INTERVAL = 0.2f;			// in seconds
	float pingTime{ 0 };

public:
	NetworkManager();
	~NetworkManager();

	void ShutDown();
	bool GetShutDownStatus() const;

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

	void ProcessInitiateLockstepPacket(
		InitiateLockstepPacket& initLockstepPacket);

	void ProcessLockstepDataPacket(
		LockstepDataPacket& dataPacket, const SocketAddress& sourceAddr);

	void ProcessHashedDataPacket(
		HashedDataPacket& dataPacket, const SocketAddress& sourceAddr);

	void ProcessDisconnectNotification(const SocketAddress& sourceAddr);

	void ProcessReconnectionReply(
		ReconnectionReply& replyPacket, const SocketAddress& sourceAddr);

	void ProcessPingPacket(
		PingPacket& pingPacket, const SocketAddress& sourceAddr);

	void ProcessPingReply(
		PingReply& pingReply, const SocketAddress& sourceAddr);

	void ProcessForceDisconnection(ForceDisconnectPacket& packet);

	void GenerateConnectionReply(
		ConnectionReply& replyPacket,
		const SocketAddress& sourceAddr,
		unsigned short assignedID);

	void GenerateReconnectionReply(ReconnectionReply& replyPacket);

	void SendPingPacket();
};


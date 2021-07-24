#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "UDPSend.h"


#include "Player.h"
#include "Packet.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "NetworkManager.h"

namespace
{
	constexpr int ownPort = 2048;
}


void UDPSend::Send(const Packet& packet)
{
	Packet pack = packet;

	//keep sending to receiver - for testing - will change next time
	sendto(data.socket, reinterpret_cast<char*>(&pack),
		sizeof(Packet), 0,
		(sockaddr*)&data.receiveAddress, sizeof(data.receiveAddress));
}

void UDPSend::StartUp(const std::string& port)
{
	UDP::StartUp();

	data.receiveAddress.sin_family = AF_INET;
	data.receiveAddress.sin_port = htons(ownPort);
	data.receiveAddress.sin_addr.s_addr = INADDR_BROADCAST;
	//data.receiveAddress.sin_addr.s_addr = inet_addr("172.30.255.255");

}

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "UDPSend.h"


#include "Player.h"
#include "Packet.h"
#include "GameObject.h"


namespace
{
	constexpr	int len = sizeof(struct sockaddr_in);
	constexpr int ownPort = 2050;
}

void UDPSend::Send()
{
	//placeholder testing
	Packet packet{ MoveType::MOVE_DOWN,glm::vec3(0,5,0) };


		//keep sending to receiver - for testing - will change next time
		sendto(data.socket, reinterpret_cast<char*>(&packet),
			sizeof(Packet), 0,
			(sockaddr*)&data.receiveAddress, sizeof(data.receiveAddress));
	
}

void UDPSend::StartUp()
{
	UDP::StartUp();
	data.receiveAddress.sin_family = AF_INET;

	data.receiveAddress.sin_port = htons(ownPort);

	data.receiveAddress.sin_addr.s_addr  = INADDR_BROADCAST;
	// subnet - 172.30.255.255
	//data.receiveAddress.sin_addr.s_addr = inet_addr("172.30.255.255");

}

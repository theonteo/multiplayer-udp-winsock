#include "UDPReceive.h"
#include <iostream>
#include "Exceptions.h"

#include "Player.h"
#include "Packet.h"
#include "GameObject.h"

namespace
{
	constexpr int ownPort = 2048;
}

Packet UDPReceive::Receive()
{
	constexpr size_t BUFFER_SIZE = 5000;
	char buffer[BUFFER_SIZE]{ 0 };
	int clientAddressSize = sizeof(data.sendAddress);

	int bytesReceived = recvfrom(data.socket, buffer, BUFFER_SIZE - 1, 0,
		(sockaddr*)&data.sendAddress, &clientAddressSize);

	//debug printout
	//std::cout << packet.hostName << std::endl;

	return *reinterpret_cast<Packet*>(&buffer);

	
}

void UDPReceive::StartUp(const std::string& port)
{
	UDP::StartUp();

	data.receiveAddress.sin_family = AF_INET;
	data.receiveAddress.sin_port = htons(ownPort);
	data.receiveAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(data.socket, (sockaddr*)&data.receiveAddress,
		sizeof(data.receiveAddress)) < 0)
	{
		closesocket(data.socket);
		throw
			exceptionHandler("bind() failed : " + WSAGetLastError(), 2);
	}

}

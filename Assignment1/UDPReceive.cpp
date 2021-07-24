#include "UDPReceive.h"
#include <iostream>
#include "Exceptions.h"

#include "Player.h"
#include "Packet.h"
#include "GameObject.h"

namespace
{
	constexpr int ownPort = 2050;
}

void UDPReceive::Receive()
{
	constexpr size_t BUFFER_SIZE = 5000;
	char buffer[BUFFER_SIZE]{ 0 };
	int clientAddressSize = sizeof(data.sendAddress);

	int bytesReceived = recvfrom(data.socket, buffer, BUFFER_SIZE - 1, 0,
		(sockaddr*)&data.sendAddress, &clientAddressSize);

	Packet packet = *reinterpret_cast<Packet*>(&buffer);

	//debug printout
	//std::cout << buffer << std::endl;
}

void UDPReceive::StartUp()
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

#include "NetworkManager.h"
#include "Player.h"

#include <string>
#include <thread>
#include <functional>

namespace
{
	constexpr size_t clientPlayerNum{ 0 };
}


void NetworkManager::Init(const std::vector<Player>& data)
{

	udp.StartUp();

	//use player 
	udp.GetAddressInfo(data[clientPlayerNum].GetPortNumber());

	udp.CreateSocket();
}





void NetworkManager::Update()
{

	std::thread receiveThread
	(std::bind(&NetworkManager::Receive, this));

	std::thread sendThread
	(std::bind(&NetworkManager::Send, this));

}

void NetworkManager::Send()
{
	while (1)
	{

	}
}

void NetworkManager::Receive()
{
	while (1)
	{

	}
}

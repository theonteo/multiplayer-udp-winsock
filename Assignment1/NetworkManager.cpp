#include "NetworkManager.h"
#include "Player.h"
#include <string>

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

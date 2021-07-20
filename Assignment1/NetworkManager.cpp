#include "NetworkManager.h"

void NetworkManager::Init(const std::vector<Player>& data)
{
	udp.StartUp();

	udp.GetAddressInfo();

	udp.CreateSocket();
}

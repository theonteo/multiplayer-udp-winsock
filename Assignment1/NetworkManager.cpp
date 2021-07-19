#include "NetworkManager.h"

void NetworkManager::Init()
{
	udp.StartUp();

	udp.GetAddressInfo();

	udp.CreateSocket();
}

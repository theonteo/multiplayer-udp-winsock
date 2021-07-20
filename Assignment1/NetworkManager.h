#pragma once

#include <string>
#include <vector>

#include "UDP.h"
#include "Player.h"

class Player;


class NetworkManager
{

	std::vector<Player> playerData;
	UDP udp;

public:

	void Init(const std::vector<Player>& data);

};


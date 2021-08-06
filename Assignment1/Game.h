#pragma once

#include <string>
#include <vector>
#include "NetworkManager.h"

class Game
{
	static NetworkManager* network;

	static void Interaction();
	static void MoveObject();
	static void MoveLighting();

public:
	static void CheckState();
	static void Init(NetworkManager* _network);
	static void Update();
	static void InitPlayer(size_t playerID);
};


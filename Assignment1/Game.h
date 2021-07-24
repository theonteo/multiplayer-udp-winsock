#pragma once

#include <string>

class Game
{

	static void Interaction();
	static void MoveObject();

public:
	static void Update();
	static void InitPlayer(const std::string& playerName);
};


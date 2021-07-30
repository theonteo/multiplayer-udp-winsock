#pragma once

#include <string>
#include <vector>
class Game
{

	static void Interaction();
	static void MoveObject();
	static void MoveLighting();

public:
	static void CheckState();
	static void Update();
	static void InitPlayer
	(const std::string& mainPlayer, const std::vector<std::string>& playerName);
};


#pragma once
#include <vector>
class Player;
class Engine
{

	std::vector<Player> ParseEntry
	(int argc, char** argv);

public:
	void Init(int argc, char** argv);
	void EngineLoop();
	void NetworkLoop();
	void Loop();
};


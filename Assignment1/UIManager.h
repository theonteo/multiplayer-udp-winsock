#pragma once
#include <map>
#include <string>
class Player;
class UIManager
{
	void RenderLobby(const std::map<std::string, Player>& data);
	void RenderGame(const std::map<std::string, Player>& data);
	void RenderResult(const std::map<std::string, Player>& data);

public:

	void Init();
	void Render(const std::map<std::string, Player>& data);
};


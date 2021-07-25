#pragma once
#include <vector>
class Player;
class UIManager
{
	void RenderLobby(const std::vector<Player>& data);
	void RenderGame(const std::vector<Player>& data);
	void RenderResult(const std::vector<Player>& data);

public:

	void Init();
	void Render(const std::vector<Player>& data);
};


#pragma once
#include <string>
#include <vector>
#include "NetworkManager.h"

class Player;
class UIManager
{
	void RenderLobby(const NetworkManager::PlayerArray& data);
	void RenderGame(const NetworkManager::PlayerArray& data);
	void RenderResult(const NetworkManager::PlayerArray& data);

public:

	void Init();
	void Render(const NetworkManager::PlayerArray& data);
};


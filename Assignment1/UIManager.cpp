#include "UIManager.h"
#include "UIText.h"
#include "GameState.h"
#include "NetworkManager.h"
#include "CommonValues.h"


void UIManager::RenderLobby(const std::vector<Player>& data)
{
	//title screen
	TextRender::RenderTextNormal
	(std::string{ "GAME.IO" }, 0.5f, 0.9f, 0, 1.2f,
		glm::vec4(1.0f, 0.75f, 0.5f, 1.0f));

	//4 player wait ui
	int index = 0;
	for (const auto& i : data)
	{
		std::string playerText{  i.GetPortName() + " not joined" };

		TextRender::RenderTextNormal
		(std::string{ playerText },
			0.5f, 0.4f - (index) * 0.05f, 0, 0.4f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		index++;
	}


}

void UIManager::RenderGame(const std::vector<Player>& data)
{
	//4 player wait ui
	int index = 0;
	for (const auto& i : data)
	{
		std::string playerText{ i.GetPortName() + " not joined" };

		TextRender::RenderTextNormal
		(std::string{ playerText },
			0.5f + (index) * 0.15f, 0.4f, 0, 0.3f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		index++;
	}
}

void UIManager::RenderResult(const std::vector<Player>& data)
{
	//4 player wait ui
	for (int i = 0; i < MAX_PLAYER; ++i)
	{

		std::string playerText{ "Player " + std::to_string(i) + " not joined" };

		TextRender::RenderTextNormal
		(std::string{ playerText },
			0.5f, 0.4f - (i) * 0.05f, 0, 0.4f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void UIManager::Init()
{
	//text setup
	TextRender::Init();
}

void UIManager::Render(const std::vector<Player>& data)
{
	switch (GameState::GetCurrentState())
	{
		//show lobby ui - which player is in lobby
	case GameState::State::STATE_LOBBY:
		RenderLobby(data);
		break;
		//show gameplay ui - score etc
	case GameState::State::STATE_GAMEPLAY:
		RenderGame(data);
		break;
		//show results ui - which player won / score
	case GameState::State::STATE_RESULTS:
		RenderResult(data);
		break;
	}
}

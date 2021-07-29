#include "UIManager.h"

#include "UIText.h"
#include "UIImage.h"

#include"Resource.h"
#include "GameState.h"
#include "NetworkManager.h"
#include "CommonValues.h"
#include "Colors.h"
#include "Texture.h"
#include <map>
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
		std::string playerText
		{ i.portName + (i.connected ? " in-game" : " not joined") };

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

	int circle =
		Resource::Texture_List.find("Textures\\circle.png")->second->textureID;
	const auto& imageShader = Resource::Shader_List.find("Shaders\\shader_ui");
	int playerNum = -1;
	for (const auto& i : data)
	{
		++playerNum;
		if (!i.connected)
			continue;

		std::string playerScore
		{ std::to_string(i.score) };

		std::string playerText
		{ i.portName + (!i.connected ? " not joined" : "") };

		const float padding = 0.075f;

		ImageRender::RenderQuad(circle, *imageShader->second,
			0.5f + (index - 2) * padding, 0.95f, 0, 0, 0, 100, 100,
			glm::vec4(col[playerNum].x, col[playerNum].y, col[playerNum].z, 1));

		//point
		TextRender::RenderTextNormal
		(std::string{ playerScore },
			0.5f + (index - 2) * padding, 0.95f, 0, 0.65f,
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		//name
		TextRender::RenderTextNormal
		(std::string{ playerText },
			0.5f + (index - 2) * padding, 0.875f, 0, 0.3f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));



		index++;
	}
}

void UIManager::RenderResult(const std::vector<Player>& data)
{
	int playerNum = 0;
	//4 player wait ui
	for (const auto& i : data)
	{
		std::string playerText
		{ i.portName + " : "+std::to_string(i.score) };

		TextRender::RenderTextNormal
		(std::string{ playerText },
			0.5f, 0.4f - (playerNum) * 0.05f, 0, 0.4f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		++playerNum;
	}
}

void UIManager::Init()
{
	//text setup
	TextRender::Init();
	ImageRender::Init();
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

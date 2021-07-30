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

void UIManager::RenderLobby(const std::map<std::string, Player>& data)
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
		{ i.second.portName + (i.second.connected ? " in-game" : " not joined") };

		TextRender::RenderTextNormal
		(std::string{ playerText },
			0.5f, 0.4f - (index) * 0.05f, 0, 0.4f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		index++;
	}
}

void UIManager::RenderGame(const std::map<std::string, Player>& data)
{
	//4 player wait ui
	int index = 0;

	int circle =
		Resource::Texture_List.find("Textures\\flag.png")->second->textureID;

	const auto& imageShader = Resource::Shader_List.find("Shaders\\shader_ui");

	int playerNum = -1;

	for (const auto& i : data)
	{
		++playerNum;
		if (!i.second.connected)
			continue;

		std::string playerScore
		{ std::to_string(i.second.score) };

		std::string playerText
		{ i.second.portName + (!i.second.connected ? " not joined" : "") };

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

void UIManager::RenderResult(const std::map<std::string, Player>& data)
{
	//4 player wait ui
	int index = 0;

	int circle =
		Resource::Texture_List.find("Textures\\circle.png")->second->textureID;

	const auto& imageShader = Resource::Shader_List.find("Shaders\\shader_ui");

	int playerNum = -1;

	//find winner
	Player p = data.begin()->second;
	int score = 0;
	for (const auto& i : data)
	{
		if (i.second.score > score)
		{
			score = i.second.score;
			p = i.second;
		}
	}



	//winner text
	TextRender::RenderTextNormal
	(std::string{ "Winner is " + p.portName },
		0.5f, 0.65f, 0, 0.65f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	for (const auto& i : data)
	{
		++playerNum;
		if (!i.second.connected)
			continue;

		std::string playerScore
		{ std::to_string(i.second.score) };

		std::string playerText
		{ i.second.portName + (!i.second.connected ? " not joined" : "") };

		const float padding = 0.075f;

		ImageRender::RenderQuad(circle, *imageShader->second,
			0.5f + (index - 2) * padding, 0.45f, 0, 0, 0, 100, 100,
			glm::vec4(col[playerNum].x, col[playerNum].y, col[playerNum].z, 1));

		//point
		TextRender::RenderTextNormal
		(std::string{ playerScore },
			0.5f + (index - 2) * padding, 0.45f, 0, 0.65f,
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		//name
		TextRender::RenderTextNormal
		(std::string{ playerText },
			0.5f + (index - 2) * padding, 0.375f, 0, 0.3f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		TextRender::RenderTextNormal
		(std::string{ "Press ESC to quit game"},
			0.5f , 0.2f, 0, 0.3f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		index++;
	}
}

void UIManager::Init()
{
	//text setup
	TextRender::Init();
	ImageRender::Init();
}

void UIManager::Render(const std::map<std::string, Player>& data)
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

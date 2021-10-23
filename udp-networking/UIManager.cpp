/******************************************************************************/
/*!
\file UIManager.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/
#include "UIManager.h"

#include "UIText.h"
#include "UIImage.h"

#include"Resource.h"
#include "GameState.h"
#include "GameObjectManager.h"
#include "CommonValues.h"
#include "Colors.h"
#include "Texture.h"
namespace
{
	std::vector<std::string> names = { "Player 1", "Player 2", "Player 3", "Player 4" };
	std::string clientName;
	size_t winnerIndex = 0;
}

void  UIManager::InitPlayer(size_t playerID)
{
	clientName = names[playerID];
}
void UIManager::RenderLobby(const NetworkManager::PlayerArray& data)
{
	//title screen
	TextRender::RenderTextNormal
	(std::string{ "PLANET.IO" }, 0.5f, 0.75f, 0, 1.75f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//connection text
	TextRender::RenderTextLight
	("Waiting for other players to connect",
		0.5f, 0.325f, 0, 0.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));

	//4 player wait ui
	int index = 0;

	int circle =
		Resource::Texture_List.find("Textures\\circle.png")->second->textureID;
	int tick =
		Resource::Texture_List.find("Textures\\tick.png")->second->textureID;
	int cross =
		Resource::Texture_List.find("Textures\\cross.png")->second->textureID;

	const auto& imageShader = Resource::Shader_List.find("Shaders\\shader_ui");

	for (const auto& i : data)
	{
		std::string playerScore
		{ std::to_string(i.score) };

		std::string playerText
		{
			"Player " + std::to_string(index + 1)
		};

		const float padding = 0.115f;
		const auto& color = colors.find(playerText)->second;
		ImageRender::RenderQuad(circle, *imageShader->second,
			(0.5f + (index - 2) * padding) + 0.05f, 0.25f, 0, 0, 0, 80, 80,
			glm::vec4(color.x, color.y, color.z, 1));

		ImageRender::RenderQuad(!i.isConnected ? cross : tick, *imageShader->second,
			(0.5f + (index - 2) * padding) + 0.05f, 0.25f, 0, 0, 0, 50, 50,
			glm::vec4(0, 0, 0, 0.6f));

		//name
		TextRender::RenderTextLight
		(std::string{ playerText },
			(0.5f + (index - 2) * padding) + 0.05f, 0.175f, 0, 0.75f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		index++;
	}
}

void UIManager::RenderGame(const NetworkManager::PlayerArray& data)
{
	//4 player wait ui
	int index = 0;

	int circle =
		Resource::Texture_List.find("Textures\\flag.png")->second->textureID;
	int disconnected =
		Resource::Texture_List.find("Textures\\disconnected.png")->second->textureID;

	const auto& imageShader = Resource::Shader_List.find("Shaders\\shader_ui");

	int playerNum = -1;

	for (const auto& i : data)
	{
		++playerNum;

		//if (i.score == 0 && !i.isConnected)
		//	continue;

		std::string playerScore
		{ std::to_string(i.score) };

		std::string playerText
		{
			"Player " + std::to_string(playerNum + 1)
		};

		const float padding = 0.075f;
		std::string playerName = "Player " + std::to_string(playerNum + 1);

		const auto& go = GameObjectManager::GameObjectList.find(playerName)->second;

		const auto& color = colors.find(playerName)->second;

		const int size = (playerName == clientName) ? 120 : 100;
		const float flagAlpha = go->enabled ? 1.0f : 0.5f;
		const auto colText = go->enabled ? glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) :
			glm::vec4(1.0f, 0.7f, 0.7f, 0.9f);

		if (!i.isConnected)
		{
			ImageRender::RenderQuad(disconnected, *imageShader->second,
				(0.5f + (index - 2) * padding) + 0.05f,
				0.81f - ((playerName == clientName) ? 0.05f : 0.0f), 0, 0, 0, size * 0.35f, size * 0.35f,
				glm::vec4(color.x, color.y, color.z, flagAlpha));
		}

		//flag
		ImageRender::RenderQuad(circle, *imageShader->second,
			(0.5f + (index - 2) * padding) + 0.05f,
			0.95f - ((playerName == clientName) ? 0.01f : 0.0f), 0, 0, 0,
			static_cast<float>(size), static_cast<float>(size),
			glm::vec4(color.x, color.y, color.z, flagAlpha));

		//point
		TextRender::RenderTextNormal
		(std::string{ playerScore },
			(0.5f + (index - 2) * padding) + 0.05f, 0.95f, 0, i.score < 100 ? 0.575f : 0.475f,
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		//name
		TextRender::RenderTextLight
		(std::string{ playerText },
			(0.5f + (index - 2) * padding) + 0.05f, 0.875f -
		((playerName == clientName) ? 0.0175f : 0.0f), 0, 0.6f,
			colText);

		index++;
	}

	//if player dead
		//title screen
	const auto& player =
		GameObjectManager::GameObjectList.find(clientName)->second;

	if (!player->enabled)
	{
		TextRender::RenderTextNormal
		(std::string{ "YOU ARE EATEN!" }, 0.5f, 0.75f, 0, 1.75f,
			glm::vec4(1.0f, 0.75f, 0.75f, 0.7f));
	}
	else {

		int score = data[0].score;

		for (size_t i = 0; i < data.size(); ++i)
		{
			// Check if player connected
			if (data[i].isConnected)
			{
				// Check if that player's score is higher than current
				score = data[i].score > score ? data[i].score : score;
				winnerIndex = data[i].score > data[winnerIndex].score ? i : winnerIndex;
			}
		}
		const auto& winner =
			GameObjectManager::GameObjectList.find(names[winnerIndex])->second;

		const auto& c = colors.find(names[winnerIndex])->second
			* glm::vec3(0.5f, 0.5f, 0.5f) + glm::vec3(0.5f, 0.5f, 0.5f);



		//instructions
		if (winner->score > 0)
			TextRender::RenderTextLight
			(std::string{ names[winnerIndex] + " is taking the lead!" },
				0.5f, 0.1f, 0, 0.8f,
				glm::vec4(c.x, c.y, c.z, 0.5f));
	}
}

void UIManager::RenderResult(const NetworkManager::PlayerArray& data)
{
	//4 player wait ui
	int index = 0;

	int circle =
		Resource::Texture_List.find("Textures\\circle.png")->second->textureID;

	const auto& imageShader = Resource::Shader_List.find("Shaders\\shader_ui");


	// Find winner

	int score = data[0].score;

	for (size_t i = 0; i < data.size(); ++i)
	{
		// Check if player connected
		if (data[i].isConnected)
		{
			// Check if that player's score is higher than current
			score = data[i].score > score ? data[i].score : score;
			winnerIndex = data[i].score > data[winnerIndex].score ? i : winnerIndex;
		}
	}

	int playerNum = -1;

	//winner text
	TextRender::RenderTextNormal
	(std::string{ "Winner is Player " + std::to_string(winnerIndex + 1) },
		0.5f, 0.65f, 0, 0.65f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	for (const auto& i : data)
	{
		++playerNum;
		if (!i.isConnected)
			continue;

		std::string playerScore
		{ std::to_string(i.score) };


		std::string playerName = "Player " + std::to_string(playerNum + 1);
		std::string playerText
		{
			playerName +
			(!i.isConnected ? " not joined" : "")
		};

		const float padding = 0.115f;
		const auto& color = colors.find(playerName)->second;

		ImageRender::RenderQuad(circle, *imageShader->second,
			(0.5f + (index - 2) * padding) + 0.05f, 0.45f, 0, 0, 0, 100, 100,
			glm::vec4(color.x, color.y, color.z, 1));

		//point
		TextRender::RenderTextNormal
		(std::string{ playerScore },
			(0.5f + (index - 2) * padding) + 0.05f, 0.45f, 0, 0.65f,
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		//name
		TextRender::RenderTextLight
		(std::string{ playerText },
			(0.5f + (index - 2) * padding) + 0.05f, 0.375f, 0, 0.6f,
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		index++;
	}
	TextRender::RenderTextLight
	(std::string{ "Press ESC to quit game" },
		0.5f, 0.2f, 0, 0.75f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void UIManager::Init()
{
	//text setup
	TextRender::Init();
	ImageRender::Init();
}

void UIManager::Render(const NetworkManager::PlayerArray& data)
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

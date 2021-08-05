/*****************************************************************************/
/*!
\file UIManager.cpp

\author Bryan Choo
\author Kevin Hartono
\author Teo Zheng Yong Theon

\par Course: cs260
\par Assignment 4
\date 1/8/21

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

#include "UIManager.h"

#include "UIText.h"
#include "UIImage.h"

#include"Resource.h"
#include "GameState.h"
#include "CommonValues.h"
#include "Colors.h"
#include "Texture.h"

void UIManager::RenderLobby(const NetworkManager::PlayerArray& data)
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
		{
			"Player " + std::to_string(index + 1) +
			(i.isConnected ? " in-game" : " not joined")
		};

		TextRender::RenderTextNormal(
			playerText,
			0.5f, 0.4f - (index) * 0.05f, 0, 0.4f,
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

	const auto& imageShader = Resource::Shader_List.find("Shaders\\shader_ui");

	int playerNum = -1;

	for (const auto& i : data)
	{
		++playerNum;
		if (!i.isConnected)
			continue;

		std::string playerScore
		{ std::to_string(i.score) };

		std::string playerText
		{
			"Player " + std::to_string(playerNum + 1) +
			(!i.isConnected ? " not joined" : "")
		};

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

void UIManager::RenderResult(const NetworkManager::PlayerArray& data)
{
	//4 player wait ui
	int index = 0;

	int circle =
		Resource::Texture_List.find("Textures\\circle.png")->second->textureID;

	const auto& imageShader = Resource::Shader_List.find("Shaders\\shader_ui");


	// Find winner
	size_t winnerIndex = 0;
	int score = data[0].score;

	for (size_t i = 1; i < data.size(); ++i)
	{
		// Check if player connected
		if (data[i].isConnected)
		{
			// Check if that player's score is higher than current
			score = data[i].score > score ? data[i].score : score;
			winnerIndex = data[i].score > score ? i : winnerIndex;
		}
	}

	int playerNum = -1;

	//winner text
	TextRender::RenderTextNormal
	(std::string{ "Winner is Player " + std::to_string(winnerIndex + 1)},
		0.5f, 0.65f, 0, 0.65f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	for (const auto& i : data)
	{
		++playerNum;
		if (!i.isConnected)
			continue;

		std::string playerScore
		{ std::to_string(i.score) };

		std::string playerText
		{
			"Player " + std::to_string(playerNum + 1) +
			(!i.isConnected ? " not joined" : "")
		};

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

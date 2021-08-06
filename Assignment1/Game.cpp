/*****************************************************************************/
/*!
\file Game.cpp

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

#include "Game.h"
#include "GameState.h"
#include "Resource.h"
#include "Camera.h"
#include "MathHelper.h"
#include "GameObjectManager.h"
#include "Window.h"
#include "DeltaTime.h"
#include "Physics.h"
#include "CommonValues.h"
#include "Lighting.h"
#include "Colors.h"

namespace
{
	std::vector<std::string> names = { "Player 1", "Player 2", "Player 3", "Player 4" };
	std::string clientName;
	float range = 4.0f;
	const float playerMoveSpeed = 5.0f;
}

void Game::InitPlayer(size_t playerID)
{
	clientName = names[playerID];
}

void Game::Interaction()
{
	const auto& player =
		GameObjectManager::GameObjectList.find(clientName)->second;

	for (const auto& i : GameObjectManager::GameObjectList)
	{
		//basic collision
		if (i.second->enabled && i.first != clientName && i.first != "Level")
			if (Physics::CircleToCircle
			(player->translate, player->scale.x,
				i.second->translate, i.second->scale.x))
			{
				//the player must have higher score to eat

				if (!player->score && i.second->score > 0)
					continue;

				if (player->score && player->score <= i.second->score)
					continue;

				player->score++;
				range = player->scale.x * 4.0f;

				i.second->enabled = false;
			}

		if (i.second->score > 0)
			i.second->scale = MathHelper::Vec3Lerp
			(i.second->scale, glm::vec3(1 + i.second->score * 0.135f),
				DeltaTime::GetDeltaTime());
	}
}

void Game::MoveObject()
{
	const auto& player =
		GameObjectManager::GameObjectList.find(clientName)->second;

	//Player control
	if (Window::getKey(GLFW_KEY_A))
	{
		player->translate.x -=
			playerMoveSpeed * DeltaTime::GetDeltaTime();
	}
	if (Window::getKey(GLFW_KEY_D))
	{
		player->translate.x +=
			playerMoveSpeed * DeltaTime::GetDeltaTime();
	}
	if (Window::getKey(GLFW_KEY_W))
	{
		player->translate.z -=
			playerMoveSpeed * DeltaTime::GetDeltaTime();
	}
	if (Window::getKey(GLFW_KEY_S))
	{
		player->translate.z +=
			playerMoveSpeed * DeltaTime::GetDeltaTime();
	}
}

void Game::MoveLighting()
{
	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		const auto& player = GameObjectManager::GameObjectList.find(names[i])->second;
		Lighting::UpdatePointLight(i, col.find(names[i])->second, player->translate);
	}
}

void Game::CheckState()
{

	//change game state
	if (Window::getKeyTriggered(GLFW_KEY_P))
	{
		GameState::AppendState();
	}
}

void Game::Update()
{
	CheckState();
	float interpolant = DeltaTime::GetDeltaTime() * 2.0f;
	const auto& cam = Resource::camera;
	if (GameState::GetCurrentState() == GameState::State::STATE_GAMEPLAY)
	{
		MoveObject();
		Interaction();
		MoveLighting();

		const auto& player =
			GameObjectManager::GameObjectList.find(clientName)->second;

		glm::vec3 append{ 0,range ,range };


		cam->SetPosition
		(MathHelper::Vec3Lerp
		(cam->getCameraPosition(), (player->translate + append), interpolant));

		cam->SetRotation
		(MathHelper::Vec2Lerp
		(cam->getCameraRotation(), glm::vec2{ -45 , -90 }, interpolant));
	}
	else {
		cam->SetPosition
		(MathHelper::Vec3Lerp
		(cam->getCameraPosition(), glm::vec3(30, 30, 30), interpolant));
		cam->SetRotation
		(MathHelper::Vec2Lerp
		(cam->getCameraRotation(), glm::vec2{ -45 , -135 }, interpolant));
	}
}

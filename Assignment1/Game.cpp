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
	const float camInterpolateSpeed = 4.0f;
	const float radiusAllowance = 0.5f;

	enum class DIRECTION : unsigned char
	{
		UP = 1,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8,
	};

	void ClearMovementFlag(unsigned char& flag)
	{
		flag ^= flag;
	}

	void UpdateMovementFlag(unsigned char& flag, const DIRECTION& direction)
	{
		flag |= static_cast<unsigned char>(direction);
	}

	bool CheckMovementFlag(const unsigned char& flag, const DIRECTION& direction)
	{
		return (flag & static_cast<unsigned char>(direction)) != 0;
	}
}

NetworkManager* Game::network = nullptr;

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
		{
			bool isColliding =
				Physics::CircleToCircle(
					player->translate,
					player->scale.x * radiusAllowance,
					i.second->translate,
					i.second->scale.x * radiusAllowance);

			if (isColliding)
			{
				//the player must have higher score to eat
				if (player->score <= i.second->score)
					continue;

				unsigned short collidingID =
					static_cast<unsigned short>(
						stoul(i.first.substr(i.first.find(' ') + 1)));

				if (i.first.find("Player") != std::string::npos)
				{
					collidingID = collidingID + 1000;
				}

				network->StartLockstep(collidingID);

				break;
			}
		}
	}

	for (const auto& i : GameObjectManager::GameObjectList)
	{
		if (i.second->score > 0)
		{
			i.second->scale =
				MathHelper::Vec3Lerp(
					i.second->scale,
					glm::vec3(1 + i.second->score * 0.135f),
					DeltaTime::GetDeltaTime());
		}
	}
}

void Game::MoveObject()
{
	const auto& player =
		GameObjectManager::GameObjectList.find(clientName)->second;

	ClearMovementFlag(player->direction);

	//Player control
	if (Window::getKey(GLFW_KEY_A))
	{
		UpdateMovementFlag(player->direction, DIRECTION::LEFT);
		player->translate.x -=
			playerMoveSpeed * DeltaTime::GetDeltaTime();
	}
	if (Window::getKey(GLFW_KEY_D))
	{
		UpdateMovementFlag(player->direction, DIRECTION::RIGHT);
		player->translate.x +=
			playerMoveSpeed * DeltaTime::GetDeltaTime();
	}
	if (Window::getKey(GLFW_KEY_W))
	{
		UpdateMovementFlag(player->direction, DIRECTION::UP);
		player->translate.z -=
			playerMoveSpeed * DeltaTime::GetDeltaTime();
	}
	if (Window::getKey(GLFW_KEY_S))
	{
		UpdateMovementFlag(player->direction, DIRECTION::DOWN);
		player->translate.z +=
			playerMoveSpeed * DeltaTime::GetDeltaTime();
	}
}

void Game::MoveLighting()
{
	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		const auto& player = GameObjectManager::GameObjectList.find(names[i])->second;

		//negative lighting if dead
		const auto& colour = 
			player->enabled ? col.find(names[i])->second : glm::vec3(-0.2f, -0.2f, -0.2f);

		Lighting::UpdatePointLight(i, colour, player->translate);
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

void Game::Init(NetworkManager* _network)
{
	network = _network;

	GameObjectManager::GameObjectList.find(names[0])->second->score = 0;
	GameObjectManager::GameObjectList.find(names[1])->second->score = 0;
	GameObjectManager::GameObjectList.find(names[2])->second->score = 0;
	GameObjectManager::GameObjectList.find(names[3])->second->score = 0;
}

//Delay is in seconds
void Game::DeadReckoning(const float& delay)
{
	if (GameState::GetCurrentState() == GameState::State::STATE_GAMEPLAY)
	{
		const float time = delay + DeltaTime::GetDeltaTime();
		for (auto& name : names)
		{
			//If name is the client. don't dead reckon.
			if (name == clientName)
				continue;

			const auto& itr =
				GameObjectManager::GameObjectList.find(name);

			//Safety, If the player is not in the object list. 
			if (itr == GameObjectManager::GameObjectList.end())
				continue;

			auto& player = itr->second;

			const auto& flag = player->direction;
			if (CheckMovementFlag(flag, DIRECTION::LEFT))
			{
				player->translate.x -=
					playerMoveSpeed * time;
			}
			if (CheckMovementFlag(flag, DIRECTION::RIGHT))
			{
				player->translate.x +=
					playerMoveSpeed * time;
			}
			if (CheckMovementFlag(flag, DIRECTION::UP))
			{
				player->translate.z -=
					playerMoveSpeed * time;
			}
			if (CheckMovementFlag(flag, DIRECTION::DOWN))
			{
				player->translate.z +=
					playerMoveSpeed * time;
			}
		}
	}
}

void Game::Update()
{
	CheckState();
	float interpolant = DeltaTime::GetDeltaTime() * camInterpolateSpeed;
	const auto& cam = Resource::camera;
	if (GameState::GetCurrentState() == GameState::State::STATE_GAMEPLAY)
	{
		MoveObject();
		DeadReckoning(0.0f);
		Interaction();
		MoveLighting();

		const auto& player =
			GameObjectManager::GameObjectList.find(clientName)->second;
			
		range = player->scale.x * 4.0f;

		glm::vec3 append{ 0,range ,range };


		cam->SetPosition(
			MathHelper::Vec3Lerp(
				cam->getCameraPosition(),
				(player->translate + append),
				interpolant));

		cam->SetRotation(
			MathHelper::Vec2Lerp(
				cam->getCameraRotation(),
				glm::vec2{ -45 , -90 },
				interpolant));
	}
	else
	{
		cam->SetPosition(
			MathHelper::Vec3Lerp(
				cam->getCameraPosition(),
				glm::vec3(30, 30, 30),
				interpolant));
				
		cam->SetRotation(
			MathHelper::Vec2Lerp(
				cam->getCameraRotation(),
				glm::vec2{ -45 , -135 },
				interpolant));
	}
}

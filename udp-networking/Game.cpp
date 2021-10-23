/******************************************************************************/
/*!
\file Game.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

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

	void PredictPosition(glm::vec3& position, const glm::vec3 velocity, const float dt)
	{
		position += velocity * dt;
	}
}

NetworkManager* Game::network = nullptr;
float Game::gameTime = 0.0f;

void Game::InitPlayer(size_t playerID)
{
	clientName = names[playerID];
}

float Game::GetGameTime()
{
	return gameTime;
}

void Game::SetGameTime(float _gameTime)
{
	gameTime = _gameTime;
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

	if (player->enabled)
	{
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

	float dt = DeltaTime::GetDeltaTime();
	gameTime += dt;
	int count = 0;
	for (auto& itr : GameObjectManager::GameObjectList)
	{
		count++;
		if (itr.second->enabled == false)
			continue;

		if (itr.first.find("item") == std::string::npos)
			continue;

		std::unique_ptr<GameObject>& item = itr.second;

		float t = sinf(gameTime + count * 0.105f);
		item->translate = item->point1 + (t * item->point2);
	}
}

void Game::MoveLighting()
{
	for (int i = 0; i < MAX_PLAYER; ++i)
	{
		const auto& player = GameObjectManager::GameObjectList.find(names[i])->second;

		//negative lighting if dead
		const auto& colour =
			player->enabled ? colors.find(names[i])->second : glm::vec3(-0.2f, -0.2f, -0.2f);

		const auto pos = player->translate + glm::vec3(0, player->scale.x / 2, 0);

		Lighting::UpdatePointLight(i, colour, pos, player->scale.x * player->scale.x);
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

			if (itr->second->enabled == false)
				continue;

			auto& player = itr->second;
			const auto& flag = player->direction;
			glm::vec3 velocity = CreateVectorFromFlag(flag);

			player->counter += time;

			float Tprime = std::min(player->counter / 0.25f, 1.0f);

			glm::vec3 blendedVel = player->clientVel + ((player->serverVel - player->clientVel) * Tprime);
			glm::vec3 projPos = player->clientPos + (blendedVel * player->counter);
			glm::vec3 projServerPos = player->serverPos + (player->serverVel * player->counter);

			player->translate = projPos + ((projServerPos - projPos) * Tprime);
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

		range = (3 + player->scale.x) * 1.5f;

		glm::vec3 append{ 0,range ,range };

		if (player->enabled)
		{
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
			(cam->getCameraPosition(), glm::vec3(20, 20, 20), interpolant));
			cam->SetRotation
			(MathHelper::Vec2Lerp
			(cam->getCameraRotation(), glm::vec2{ -45 , -135 }, interpolant));
		}
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

glm::vec3 Game::CreateVectorFromFlag(unsigned char flag)
{
	glm::vec3 translate = glm::vec3(0, 0, 0);
	if (CheckMovementFlag(flag, DIRECTION::LEFT))
	{
		translate.x -=
			playerMoveSpeed;
	}
	if (CheckMovementFlag(flag, DIRECTION::RIGHT))
	{
		translate.x +=
			playerMoveSpeed;
	}
	if (CheckMovementFlag(flag, DIRECTION::UP))
	{
		translate.z -=
			playerMoveSpeed;
	}
	if (CheckMovementFlag(flag, DIRECTION::DOWN))
	{
		translate.z +=
			playerMoveSpeed;
	}

	return translate;
}
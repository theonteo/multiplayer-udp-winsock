#include "Game.h"
#include "GameState.h"
#include "Resource.h"
#include "Camera.h"
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
					player->scale.x,
					i.second->translate,
					i.second->scale.x);

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
		if (i.second->score != -1)
		{
			i.second->scale = glm::vec3(1 + i.second->score * 0.135f);
		}
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
		Lighting::UpdatePointLight(i,col[i], player->translate);
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

void Game::Update()
{
	MoveLighting();

	CheckState();
	
	const auto& cam = Resource::camera;
	if (GameState::GetCurrentState() == GameState::State::STATE_GAMEPLAY)
	{
		MoveObject();
		Interaction();

		const auto& player =
			GameObjectManager::GameObjectList.find(clientName)->second;
		range = player->scale.x * 4.0f;
		glm::vec3 append{ range,range + 1.0f,range };
		cam->SetPosition(player->translate + append);
		cam->SetRotation(glm::vec2{ -45 , -135 });
	}
	else
	{
		cam->SetPosition(glm::vec3(30, 30, 30));
		cam->SetRotation(glm::vec2{ -45 , -135 });
	}
}

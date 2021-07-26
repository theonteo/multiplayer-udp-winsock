#include "Game.h"
#include "GameState.h"
#include "Resource.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "Window.h"
#include "DeltaTime.h"
#include "Physics.h"

namespace
{
	std::string goTarget{ "" };
	float range = 4.0f;
	const float playerMoveSpeed = 5.0f;
}
void Game::InitPlayer(const std::string& playerName)
{
	goTarget = playerName;
}
void Game::Interaction()
{
	const auto& player =
		GameObjectManager::GameObjectList.find(goTarget)->second;

	for (const auto& i : GameObjectManager::GameObjectList)
	{
		//basic collision
		if (i.second->enabled && i.first != goTarget && i.first != "Level")
			if (Physics::CircleToCircle
			(player->translate, player->scale.x,
				i.second->translate, i.second->scale.x))
			{
				range = player->scale.x * 4.0f;
				player->scale *= 1.02f;
				i.second->enabled = false;
			}
	}
}

void Game::MoveObject()
{
	const auto& player =
		GameObjectManager::GameObjectList.find(goTarget)->second;

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
	MoveObject();
	Interaction();

	const auto& cam = Resource::camera;
	const auto& player =
		GameObjectManager::GameObjectList.find(goTarget)->second;
	glm::vec3 append{ range,range + 1.0f,range };

	cam->SetPosition(player->translate + append);
	cam->SetRotation(glm::vec2{ -45 , -135 });
}

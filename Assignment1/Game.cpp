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
				player->score++;
				range = player->scale.x * 4.0f;

				i.second->enabled = false;
			}

		if (i.second->score > 0)
			i.second->scale = glm::vec3(1 + i.second->score * 0.135f);
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
	
	const auto& cam = Resource::camera;
	if (GameState::GetCurrentState() == GameState::State::STATE_GAMEPLAY)
	{
		MoveObject();
		Interaction();

		const auto& player =
			GameObjectManager::GameObjectList.find(goTarget)->second;
		glm::vec3 append{ range,range + 1.0f,range };
		cam->SetPosition(player->translate + append);
		cam->SetRotation(glm::vec2{ -45 , -135 });
	}
	else {
		cam->SetPosition(glm::vec3(30, 30, 30));
		cam->SetRotation(glm::vec2{ -45 , -135 });
	}
}

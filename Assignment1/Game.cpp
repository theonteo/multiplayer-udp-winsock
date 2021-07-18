#include "Game.h"
#include "Resource.h"
#include "Camera.h"
#include "GameObjectManager.h"
#include "Window.h"
#include "DeltaTime.h"

namespace
{
	std::string goTarget{ "Player" };
	const float range = 7.0f;
	const float playerMoveSpeed = 5.0f;
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

void Game::Update()
{
	const auto& cam = Resource::camera;

	const auto& player = 
		GameObjectManager::GameObjectList.find(goTarget)->second;

	glm::vec3 append{ range,range+1.0f,range };

	MoveObject();

	cam->SetPosition(player->translate + append);
	cam->SetRotation(glm::vec2{ -45 , -135 });
}

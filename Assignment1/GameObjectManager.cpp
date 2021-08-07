/*****************************************************************************/
/*!
\file GameObjectManager.cpp

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

#include "GameObjectManager.h"
#include "Resource.h"
#include <Colors.h>
std::map<std::string, std::unique_ptr<GameObject>>
GameObjectManager::GameObjectList;

namespace
{
	constexpr size_t maxPlayerCount = 4;
}

/******************************************************************************/
/*!
\brief  assign render objects
*/
/******************************************************************************/
void GameObjectManager::Create()
{
	//add one player
	AddPlayer();

	AddScatterObjects();

	AddLevel();
}

void GameObjectManager::AddPlayer()
{


	for (size_t i = 0; i < maxPlayerCount; ++i)
	{
		std::unique_ptr<GameObject> go = std::make_unique<GameObject>();
		//set initial object
		go->translate = glm::vec3(0.0f + (i * 2), 0.0f, 0.0f);
		go->rotation = glm::vec3(0, 0, 0);
		go->scale = glm::vec3(1, 1, 1);

		go->GameObjectName = "Main Object";
		go->Model = "Models\\Sphere.obj";
		go->shader = "Shaders\\shader";

		std::string name = "Player " + std::to_string(i + 1);

		go->colour = col.find(name)->second * 2.0f;

		GameObjectList.insert
		(std::pair<std::string, std::unique_ptr<GameObject>>
		("Player " + std::to_string(i + 1), std::move(go)));
	}
}

void GameObjectManager::AddScatterObjects()
{
	for (size_t i = 0; i < 250; ++i)
	{

	

		float x = static_cast<float>(((rand() % 100) - 50)) *1.25f;
		float z = static_cast<float>(((rand() % 100) - 50)) * 1.25f;

		std::unique_ptr<GameObject> go = std::make_unique<GameObject>();

		glm::vec3 pos{ x, 0.0f, z };
		if (glm::length(pos) < 5.0f)
			continue;

		//set initial object
		go->translate = pos;
		go->rotation = glm::vec3(0, 0, 0);
		go->scale = glm::vec3(0.3f, 0.3f, 0.3f);
		go->colour = glm::vec3(5.0f, 5.0f, 5.0f);

		go->GameObjectName = "point";
		go->Model = "Models\\Sphere.obj";
		go->shader = "Shaders\\shader";

		GameObjectList.insert
		(std::pair<std::string, std::unique_ptr<GameObject>>
		("item " + std::to_string(i), std::move(go)));

	}
}

void GameObjectManager::AddLevel()
{
	//add one floor

	std::unique_ptr<GameObject> go = std::make_unique<GameObject>();

	//set initial object
	go->translate = glm::vec3(0.0f, -1.0f, 0.0f);
	go->rotation = glm::vec3(0, 0, 0);
	go->scale = glm::vec3(5000, 1, 5000);
	go->colour = glm::vec3(0.05f, 0.05f, 0.05f);


	go->GameObjectName = "Main Object";
	go->Model = "Models\\cube.obj";
	go->shader = "Shaders\\shader";

	GameObjectList.insert
	(std::pair<std::string, std::unique_ptr<GameObject>>
	("Level", std::move(go)));
}

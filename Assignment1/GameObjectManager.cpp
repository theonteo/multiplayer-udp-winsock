#include "GameObjectManager.h"
#include "Resource.h"

std::map<std::string, std::unique_ptr<GameObject>>
GameObjectManager::GameObjectList;

namespace
{
	constexpr size_t maxPlayerCount = 4;

	//default player colours
	const std::vector<glm::vec3>	col({
		//blue
		{ 0.0f / 255.0f,191.0f / 255.0f, 255.0f / 255.0f},
		//red
		{255.0f / 255.0f,0.0f / 255.0f, 75.0f / 255.0f},
		//green
		{ 174.0f / 255.0f, 255.0f / 255.0f,0.0f / 255.0f},
		//orange
		{ 255.0f / 255.0f, 150.0f / 255.0f, 0.0f / 255.0f},
		});
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
		go->Model = (*Resource::Model_List.find("Models\\Sphere.obj")).second;
		go->shader = "Shaders\\shader";


		go->colour =col[i] * 2.0f;

		GameObjectList.insert
		(std::pair<std::string, std::unique_ptr<GameObject>>
		("player" + std::to_string(i + 1), std::move(go)));
	}
}

void GameObjectManager::AddScatterObjects()
{
	for (size_t i = 0; i < 50; ++i)
	{

		std::unique_ptr<GameObject> go = std::make_unique<GameObject>();

		float x = static_cast<float>(((rand() % 100) - 50)) * 0.5f;
		float z = static_cast<float>(((rand() % 100) - 50)) * 0.5f;

		//set initial object
		go->translate = glm::vec3(x, 0.0f, z);
		go->rotation = glm::vec3(0, 0, 0);
		go->scale = glm::vec3(0.25f, 0.25f, 0.25f);
		go->colour = glm::vec3(0.2f, 0.2f, 0.2f);

		go->GameObjectName = "point";
		go->Model = (*Resource::Model_List.find("Models\\Sphere.obj")).second;
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
	go->scale = glm::vec3(50, 1, 50);

	go->GameObjectName = "Main Object";
	go->Model = (*Resource::Model_List.find("Models\\cube.obj")).second;
	go->shader = "Shaders\\shader";

	GameObjectList.insert
	(std::pair<std::string, std::unique_ptr<GameObject>>
	("Level", std::move(go)));
}

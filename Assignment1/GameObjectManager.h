#ifndef _GAMEOBJECTMANAGER_H
#define _GAMEOBJECTMANAGER_H

#include <map>
#include <string>
#include <memory>
#include "GameObject.h"
class GameObjectManager
{
	static void AddPlayer();
	static void AddScatterObjects();
	static void AddLevel();

public:
	//store data
	static void Create();

	static std::map<std::string, std::unique_ptr<GameObject>>
		GameObjectList;
};
#endif

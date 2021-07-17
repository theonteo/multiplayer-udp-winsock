#ifndef _GAMEOBJECTMANAGER_H
#define _GAMEOBJECTMANAGER_H

#include <map>
#include <string>

class GameObject;

class GameObjectManager
{

public:

	//store data

	static std::map<std::string, GameObject*>GameObjectList;
};
#endif

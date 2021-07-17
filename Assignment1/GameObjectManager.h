#ifndef _GAMEOBJECTMANAGER_H
#define _GAMEOBJECTMANAGER_H

#include <map>
#include <string>
#include <memory>
#include "GameObject.h"
class GameObjectManager
{

public:

	//store data

	static std::map<std::string, std::unique_ptr<GameObject>>GameObjectList;
};
#endif

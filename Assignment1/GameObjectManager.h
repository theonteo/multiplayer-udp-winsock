/*****************************************************************************/
/*!
\file GameObjectManager.h

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

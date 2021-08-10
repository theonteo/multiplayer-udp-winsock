/******************************************************************************/
/*!
\file GameObjectManager.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\par email: c.choo\@digipen.edu
\par email: kevin.hartono\@digipen.edu
\par email: zhengyongtheon.teo\@digipen.edu

\par DigiPen login: c.choo
\par DigiPen login: kevin.hartono
\par DigiPen login: zhengyongtheon.teo

\par Course: CS260-A
\par Assignment 4
\date 01/08/2021
\brief
This file contains the declarations of the Game Object Manager Class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

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

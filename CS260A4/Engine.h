/******************************************************************************/
/*!
\file Engine.h
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
This file contains the declarations of the Engine class used as the main driver of
game engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#pragma once

#include <map>
#include <string>

#include "NetworkManager.h"
#include "Interface.h"
#include "Resource.h"
#include "Window.h"
#include "Camera.h"
#include "Lighting.h"
#include "UIManager.h"

class Engine
{

	NetworkManager network;
	Interface interface_game;
	Resource main_editor;
	Window mainWindow;
	Camera camera;
	Lighting lighting;
	UIManager ui;

public:
	void Init(char** argv);
	void EngineLoop();
	void NetworkLoop();
	void Loop();
	
	NetworkManager* GetNetworkManager();
};


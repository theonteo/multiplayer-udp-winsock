/******************************************************************************/
/*!
\file Engine.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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


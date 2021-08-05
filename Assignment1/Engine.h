/*****************************************************************************/
/*!
\file
\author
\par email:
\par DigiPen login:
\par Course: cs260
\par Assignment 4
\date

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

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
};


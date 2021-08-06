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

class Engine
{
	NetworkManager network;

public:
	void Init(char** argv);
	void EngineLoop();
	void NetworkLoop();
	void Loop();
	
	NetworkManager* GetNetworkManager();
};


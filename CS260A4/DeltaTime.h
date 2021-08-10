/******************************************************************************/
/*!
\file DeltaTime.h
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
This file contains the definitions of the Delta time class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#pragma once

#include <GL/glew.h>

class DeltaTime
{
public:
	static GLfloat deltaTime;
	static GLfloat deltaTimeUnscaled;
	static GLfloat lastTime;

	static GLfloat engineRunTime;
	static GLfloat engineRunTimeUnscaled;
	static GLfloat gameTime;
	static GLfloat TimeScale;

	static GLfloat fixedDeltaTime;
	static GLfloat fixedDeltaTimeAccum;

	//init
	static void Init();

	//calculate delta time
	static void CalculateDeltaTime();

	//get delta time
	static float GetDeltaTime();

	//get time scale
	static const float& GetTimeScale();

	//get unscaled time
	static float GetDeltaTimeUnScaled();

	//get time scale
	static void SetTimeScale(const float& deltaT);

	//get constructor
	DeltaTime();

	//destructor
	~DeltaTime();
};

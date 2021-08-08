/******************************************************************************/
/*!
\file DeltaTime.cpp
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

#include "DeltaTime.h"

#include <GLFW/glfw3.h>

GLfloat DeltaTime::deltaTime;
GLfloat DeltaTime::deltaTimeUnscaled;
GLfloat DeltaTime::engineRunTimeUnscaled;
GLfloat DeltaTime::lastTime;
GLfloat DeltaTime::engineRunTime;
GLfloat DeltaTime::gameTime;
GLfloat DeltaTime::TimeScale = 1.0f;
GLfloat DeltaTime::fixedDeltaTime = 1.0f / 60.0f;
GLfloat DeltaTime::fixedDeltaTimeAccum = 0.0f;

/******************************************************************************/
/*!
\brief     calculate delta time
*/
/******************************************************************************/
void DeltaTime::CalculateDeltaTime()
{
	GLfloat now = static_cast<GLfloat>(glfwGetTime());
	deltaTimeUnscaled = (now - lastTime); // > 1 / 20.0f ? 1 / 20.0f : (now - lastTime);
	deltaTime = deltaTimeUnscaled * TimeScale;
	lastTime = now;

	engineRunTime += deltaTime;
	engineRunTimeUnscaled += deltaTimeUnscaled;
	gameTime += deltaTime;
}

/******************************************************************************/
/*!
\brief     Initiate delta time
*/
/******************************************************************************/
void DeltaTime::Init()
{
	lastTime = 0.0f;
}

/******************************************************************************/
/*!
\brief     return delta time
*/
/******************************************************************************/
float DeltaTime::GetDeltaTime()
{
	return deltaTime;
}

/******************************************************************************/
/*!
\brief     get unscaled delta time
*/
/******************************************************************************/
float DeltaTime::GetDeltaTimeUnScaled()
{
	return deltaTimeUnscaled;
}

/******************************************************************************/
/*!
\brief    get timescale
*/
/******************************************************************************/
const float& DeltaTime::GetTimeScale()
{
	return TimeScale;
}

/******************************************************************************/
/*!
\brief     set timescale
*/
/******************************************************************************/
void DeltaTime::SetTimeScale(const float& deltaT)
{
	TimeScale = deltaT;
}

/******************************************************************************/
/*!
\brief    deltatime constructor
*/
/******************************************************************************/

DeltaTime::DeltaTime()
{
}

/******************************************************************************/
/*!
\brief    deltatime destructor
*/
/******************************************************************************/
DeltaTime::~DeltaTime()
{
}

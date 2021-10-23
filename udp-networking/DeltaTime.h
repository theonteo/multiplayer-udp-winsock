/******************************************************************************/
/*!
\file DeltaTime.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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

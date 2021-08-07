/*****************************************************************************/
/*!
\file DeltaTime.h

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

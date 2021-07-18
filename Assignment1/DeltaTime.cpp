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

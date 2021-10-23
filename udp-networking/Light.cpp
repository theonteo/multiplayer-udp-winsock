/******************************************************************************/
/*!
\file Light.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#include "Light.h"

/******************************************************************************/
/*!
\brief  light constructor
*/
/******************************************************************************/
Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

/******************************************************************************/
/*!
\brief light constructor
*/
/******************************************************************************/
Light::Light
(GLfloat shadowWidth,GLfloat shadowHeight,
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity)
{

	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
	shadowMap = new ShadowMap();
	shadowMap->Init(static_cast<GLuint>(shadowWidth), static_cast<GLuint>(shadowHeight));
}
/******************************************************************************/
/*!
\brief get shadowmap
*/
/******************************************************************************/
ShadowMap* Light::GetShadowMap()
{
	return shadowMap;
}


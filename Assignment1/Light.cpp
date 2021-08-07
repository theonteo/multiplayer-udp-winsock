/*****************************************************************************/
/*!
\file Light.cpp

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


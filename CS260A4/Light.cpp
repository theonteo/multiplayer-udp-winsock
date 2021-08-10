/******************************************************************************/
/*!
\file Light.cpp
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
This file contains the definitions of the light class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
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


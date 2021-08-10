/******************************************************************************/
/*!
\file Light.h
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
This file contains the declarations of the light class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#ifndef LIGHT_H
#define LIGHT_H

#include <glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShadowMap.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Exceptions.h"

class Interface;
class Light
{
	friend Interface;
public:

	Light(GLfloat shadowWidth,GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity);

	ShadowMap* GetShadowMap();
	Light();
protected:
	ShadowMap* shadowMap;
	glm::vec3 colour;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
	glm::mat4 lightProj;

};

#endif
/*****************************************************************************/
/*!
\file Light.h

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

#ifndef LIGHT_H
#define LIGHT_H

#include <glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ShadowMap.h>

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
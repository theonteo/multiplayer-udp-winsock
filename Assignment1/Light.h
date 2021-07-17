/*****************************************************************************/
/*!
\file
\author
\par email:
\par DigiPen login:
\par Course: cs260
\par Assignment 4
\date

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
/******************************************************************************/
/*!
\file Light.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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
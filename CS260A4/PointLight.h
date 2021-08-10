/******************************************************************************/
/*!
\file PointLight.h
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
This file contains the declarations of the point light class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class Interface;
class PointLight :
	public Light
{
	friend Interface;
public:
	PointLight();
	PointLight(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat con,GLfloat lin,GLfloat exp);
	 
	void UseLight(GLint ambientIntensityLocation,
		GLint ambientColourLocation,
		GLint diffuseIntensityLocation, GLint positionLocation,
		GLint constantLocation,GLint linearLocation,GLint exponentLocation);

	void SetIntensity(float pos);
	void SetPosition(const glm::vec3& pos);
	void SetColour(const glm::vec3& col);

protected:
	glm::vec3 position;
	GLfloat constant, linear, exponent;

};

#endif
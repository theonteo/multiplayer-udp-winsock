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

protected:
	glm::vec3 position;
	GLfloat constant, linear, exponent;

};

#endif
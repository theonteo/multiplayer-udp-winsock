/*****************************************************************************/
/*!
\file Spotlight.cpp

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

#include "SpotLight.h"


/******************************************************************************/
/*!
\brief  spotlight constructor
*/
/******************************************************************************/
SpotLight::SpotLight():PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
}

/******************************************************************************/
/*!
\brief  spotlight constructor
*/
/******************************************************************************/
SpotLight::SpotLight(GLfloat shadowWidth, GLfloat shadowHeight,
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	GLfloat con, GLfloat lin, GLfloat exp,
	GLfloat edg) :
	PointLight(shadowWidth, shadowHeight,red,
		green, blue, aIntensity, dIntensity,
		xPos, yPos, zPos, con, lin, exp)
{

	direction =glm::normalize( glm::vec3(xDir, yDir, zDir));
	edge = edg;
	procEdge = cosf(glm::radians(edge));

}

/******************************************************************************/
/*!
\brief use light
*/
/******************************************************************************/
void SpotLight::UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
	GLint diffuseIntensityLocation, GLint positionLocation,
	GLint directionLocation,
	GLint constantLocation, GLint linearLocation, GLint exponentLocation,
	GLint edgeLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);

}

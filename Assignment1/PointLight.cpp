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

#include "PointLight.h"

/******************************************************************************/
/*!
\brief point light constructor
*/
/******************************************************************************/
PointLight::PointLight():Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;
}

/******************************************************************************/
/*!
\brief  pointlight constructor
*/
/******************************************************************************/
PointLight::PointLight
(GLfloat shadowWidth, GLfloat shadowHeight,
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat con, GLfloat lin, GLfloat exp):
	Light(1024,1024,red,green,blue,aIntensity,dIntensity)
{
	position = glm::vec3(xPos, yPos, zPos);
	constant = con;
	linear = lin;
	exponent = exp;
}

/******************************************************************************/
/*!
\brief  use light
*/
/******************************************************************************/
void PointLight::UseLight(GLint ambientIntensityLocation,
	GLint ambientColourLocation,
	GLint diffuseIntensityLocation, GLint positionLocation,
	GLint constantLocation, GLint linearLocation, GLint exponentLocation)
{

	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation,linear);
	glUniform1f(exponentLocation, exponent);

}

void PointLight::SetPosition(const glm::vec3& pos)
{
	position = pos;
}

void PointLight::SetColour(const glm::vec3& col)
{
	colour = col;
}

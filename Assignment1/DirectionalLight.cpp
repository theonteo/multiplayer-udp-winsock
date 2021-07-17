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

#include "DirectionalLight.h"

/******************************************************************************/
/*!
\brief  directional light constructor
*/
/******************************************************************************/
DirectionalLight::DirectionalLight():Light()
{
	direction = glm::vec3(-45.0f, -1.0f, 0.0f);
}
/******************************************************************************/
/*!
\brief  directional light constructor
*/
/******************************************************************************/
DirectionalLight::DirectionalLight
(GLfloat shadowWidth, GLfloat shadowHeight,
	GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir) 
	: Light(shadowWidth,shadowHeight,
		red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);
	lightProj = glm::ortho(-3.0f, 3.0f, -3.0f,3.0f, 0.1f, 50.0f);

}
/******************************************************************************/
/*!
\brief set light rotation
*/
/******************************************************************************/
void DirectionalLight::SetLightRotation(glm::vec3 rotation)
{
	// rotation angle about X-axis (pitch)
	float theta = glm::radians(rotation.x);
	float sx = sin(theta);
	float cx = cos(theta);

	// rotation angle about Y-axis (yaw)
	theta = glm::radians(rotation.y);
	float sy = sin(theta);
	float cy = cos(theta);

	// rotation angle about Z-axis (roll)
	theta = glm::radians(rotation.z);
	float sz = sin(theta);
	float cz = cos(theta);

	glm::vec3 front;
	front.y = sy;
	front.z = -sx * cy;
	front.x = cx * cy;
	direction = front;
}

/******************************************************************************/
/*!
\brief  use light
*/
/******************************************************************************/
void DirectionalLight::UseLight
(GLint ambientIntensityLocation, GLint ambientColourLocation,
	GLint diffuseIntensityLocation, GLint directionLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

/******************************************************************************/
/*!
\brief  calculate light transform
*/
/******************************************************************************/
glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return lightProj * glm::lookAt
	(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}


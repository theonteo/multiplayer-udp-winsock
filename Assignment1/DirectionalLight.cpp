/******************************************************************************/
/*!
\file DirectionalLight.cpp
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
This file contains the definitions of the Directional Light class used by the 
graphics engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "DirectionalLight.h"
#include "Resource.h"
#include "Camera.h"

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
	lightProj = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f,300.0f);

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

	glm::mat4 model = glm::translate(glm::mat4(1.0f), -Resource::camera->getCameraPosition() + front * 75.0f);
	return  lightProj *  glm::lookAt
	(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))*model;
}


/******************************************************************************/
/*!
\file DirectionalLight.h
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
This file contains the declarations of the Directional Light class used by the 
graphics engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "Light.h"
class DirectionalLight:public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir);
	void SetLightRotation(glm::vec3 rotation);
	void UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
		GLint diffuseIntensityLocation, GLint directionLocation);
	
	glm::mat4 CalculateLightTransform();


private:
	glm::vec3 front{};
	glm::vec3 direction{};
};

#endif
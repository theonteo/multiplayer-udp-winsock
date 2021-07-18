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

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include <Light.h>
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
	glm::vec3 front;
	glm::vec3 direction;
};

#endif
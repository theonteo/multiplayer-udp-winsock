/******************************************************************************/
/*!
\file PointLight.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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
/*****************************************************************************/
/*!
\file Spotlight.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "PointLight.h"
class SpotLight :
	public PointLight
{
public:
	SpotLight();

	SpotLight(GLfloat shadowWidth, GLfloat shadowHeight,
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat con, GLfloat lin, GLfloat exp,
		GLfloat edg);

	void UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
		GLint diffuseIntensityLocation, GLint positionLocation,
		GLint directionLocation,
		GLint constantLocation, GLint linearLocation, GLint exponentLocation,
		GLint edgeLocation);

private:
	glm::vec3 direction;
	GLfloat edge, procEdge;
};

#endif

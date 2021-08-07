/*****************************************************************************/
/*!
\file Spotlight.h

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

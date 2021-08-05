/*****************************************************************************/
/*!
\file ShadowMap.h

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

#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <stdio.h>
#include <GL/glew.h>
class ShadowMap
{
public:
	ShadowMap();
	GLuint shadowMap;
	GLuint FBO;
	virtual bool Init(GLuint width, GLuint height);
	virtual void Write();
	virtual void Read(GLenum textureUnit);
	GLuint GetShadowWidth() { return shadowWidth; }
	GLuint GetShadowHeight() { return shadowHeight; }
	~ShadowMap();

protected:
	GLuint shadowWidth, shadowHeight;



};

#endif

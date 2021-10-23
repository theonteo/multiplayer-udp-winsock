/******************************************************************************/
/*!
\file ShadowMap.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

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

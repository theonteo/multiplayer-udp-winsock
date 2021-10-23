/******************************************************************************/
/*!
\file UIImage.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#pragma once
#include <GL/glew.h>
#include <glm.hpp>
class Shader;
namespace ImageRender
{
	void Init();

	void RenderQuad(int texID, Shader& shader, GLfloat _x,
		GLfloat _y, GLfloat _z, GLfloat _localx, GLfloat _localy,
		GLfloat scaleX, GLfloat scaleY,
		const glm::vec4& color);
}


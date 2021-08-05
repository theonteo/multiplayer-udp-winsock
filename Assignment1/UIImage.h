/*****************************************************************************/
/*!
\file UIImage.h

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


/******************************************************************************/
/*!
\file UIImage.h
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
This file contains the declarations of the UI Image Class used to render UI
Elements.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
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


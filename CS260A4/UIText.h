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
This file contains the definitions of the UI Image Class used to render UI
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

#include "ft2build.h"
#include <string>
#include <GL/glew.h>
#include <vector>
#include <glm.hpp>
class Shader;

namespace TextRender
{
	struct Character
	{
		// ID handle
		GLuint TextureID;

		// Size of glyph
		glm::vec2 Size;

		// Offset from baseline to left/top of glyph
		glm::vec2 Bearing;

		// Offset to advance to next glyph
		GLuint Advance;
	};

	class Font
	{
	public:
		size_t fontSize;
		std::string fontPath;
		Font(const std::string& fontPath, size_t fontSize);
		std::vector<Character> allCharacters;
	};


	void RenderText(Font* _character, Shader& shader, const std::string& text,
		GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _localx, GLfloat _localy,
		GLfloat scale, const glm::vec4& color, int start, int end);

	void RenderTextNormal
	(const std::string& text, GLfloat _x, GLfloat _y, GLfloat _z,
		GLfloat scale, const glm::vec4& color);

	void RenderTextLight
	(const std::string& text, GLfloat _x, GLfloat _y, GLfloat _z,
		GLfloat scale, const glm::vec4& color);

	void Init();
}


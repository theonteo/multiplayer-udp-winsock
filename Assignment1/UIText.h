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

	void Init();
}


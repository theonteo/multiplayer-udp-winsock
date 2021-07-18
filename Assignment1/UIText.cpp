#include "UIText.h"
#include "Resource.h"
#include "ft2build.h"
#include "Camera.h"
#include "CommonValues.h"
#include "Shader.h"
#include "freetype/freetype.h"
#include "Graphics.h"
#include <iostream>

/******************************************************************************/
/*!
\brief  render text
*/
/******************************************************************************/
namespace TextRender
{
	GLuint VAO, VBO;

	Font* font;

	/******************************************************************************/
	/*!
	\brief  init
	*/
	/******************************************************************************/
	void Init()
	{
		font = new Font("Fonts/font.ttf", 60);

		// Configure VAO/VBO for texture quads
		Graphics::GenVertexArrayDynamic(VAO, VBO, NULL, sizeof(GLfloat) * 6 * 4);
		Graphics::EnableVertexArrayAttribute(0, 4, 4 * sizeof(GLfloat), 0);
	}

	/******************************************************************************/
	/*!
	\brief   set if transparency is enabled
	*/
	/******************************************************************************/
	inline void EnableTransparency(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glDisable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_BLEND);
			//	glEnable(GL_DEPTH_TEST);
			glBlendFunc(GL_ONE, GL_ZERO);
		}
	}
	/******************************************************************************/
/*!
\brief   small text render
*/
/******************************************************************************/
	void RenderTextNormal
	(const std::string& text, GLfloat _x, GLfloat _y, GLfloat _z, 
		GLfloat scale, const glm::vec4& color)
	{
		RenderText(font, *Resource::Shader_List.find("Shaders\\shader_text")->second, text,
			_x, _y, _z, 0, 0,
			scale, color, 0, 9999);
	}
	void RenderText(Font* _character, Shader& shader, const std::string& text,
		GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _localx, GLfloat _localy,
		GLfloat scale, const glm::vec4& color, int start, int end)
	{
		EnableTransparency(true);

		// Activate corresponding render state	
		shader.UseShader();

		const auto& cam = Resource::camera;

		GLfloat camWidth = WINDOW_WIDTH;
		GLfloat camHeight = WINDOW_HEIGHT;


		GLfloat x = _x * camWidth - camWidth / 2;
		GLfloat y = _y * camHeight - camHeight / 2;

		x += _localx;
		y += _localy;

	glm::mat4 temp{ 1.0f };
		glm::vec3 trans = glm::vec3{ 0, 0, _z };
		temp = glm::translate(temp, trans);

		glm::mat4 projection = glm::ortho(0.0f, camWidth, 0.0f, camHeight);

		Graphics::UniformMat4(shader.GetModelLocation(), temp);
		Graphics::UniformMat4(shader.GetProjectionLocation(), projection);
		Graphics::UniformVec4(shader.GetColourLocation(), color);

		Graphics::ActiveTexture(0);

		// Iterate through all characters
		std::string::const_iterator c;

		float xAdvance = 0.0f;
		int index = 0;
		const auto& textEnd = text.end();
		for (c = text.begin(); c != textEnd; c++)
		{
			Character ch = _character->allCharacters[*c];
			xAdvance += (ch.Advance >> 6) * scale;
		}

		for (c = text.begin(); c != textEnd; c++)
		{
			Character ch = _character->allCharacters[*c];
			if (!(index < start || index > end))
			{
				GLfloat xpos =
					(x + ch.Bearing.x * scale)
					- ((xAdvance * 0.5f))
					+ camWidth * 0.5f;


				GLfloat ypos = (y - (ch.Size.y - ch.Bearing.y) * scale) - ((_character->fontSize * 0.25f) * scale)
					+ camHeight * 0.5f;

				GLfloat w = ch.Size.x * scale;
				GLfloat h = ch.Size.y * scale;
				// Update VBO for each character
				GLfloat vertices[6][4] = {
					{xpos, ypos + h, 0.0, 0.0},
					{xpos, ypos, 0.0, 1.0},
					{xpos + w, ypos, 1.0, 1.0},

					{xpos, ypos + h, 0.0, 0.0},
					{xpos + w, ypos, 1.0, 1.0},
					{xpos + w, ypos + h, 1.0, 0.0}
				};
				// Render glyph texture over quad
				Graphics::BindTexture(ch.TextureID);


				Graphics::BindVertexSubBuffer(VBO, (float*)vertices, sizeof(vertices));

				Graphics::DrawTrianglesArray(VAO, 6);
			}
			index++;
			x += (ch.Advance >> 6) * scale;
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		Graphics::EnableTransparency(false);
	}

	/******************************************************************************/
	/*!
	\brief  font constructor
	*/
	/******************************************************************************/
	Font::Font(const std::string& _fontPath, size_t _fontSize)
		: fontSize{ _fontSize },
		fontPath{ _fontPath }
	{
		//load ft lib
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			std::cout<<"ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		//load one font
		FT_Face face;
		if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		FT_Set_Pixel_Sizes(face, 0, static_cast<FT_UInt>(fontSize));

		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;


		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

		//load in 128 characters
		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
				);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::vec2{static_cast<int>(face->glyph->bitmap.width), static_cast<int>(face->glyph->bitmap.rows)},
				glm::vec2{face->glyph->bitmap_left, face->glyph->bitmap_top},
				static_cast<GLuint>(face->glyph->advance.x)
			};
			allCharacters.push_back(character);
		}


		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
}
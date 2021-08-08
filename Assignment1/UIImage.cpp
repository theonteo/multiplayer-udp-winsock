/******************************************************************************/
/*!
\file UIImage.cpp
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

#include "UIImage.h"
#include "Graphics.h"
#include "CommonValues.h"
#include "Shader.h"
#include "Resource.h"

namespace ImageRender
{
	GLuint VAO, VBO;

	void Init()
	{
		// Configure VAO/VBO for texture quads
		Graphics::GenVertexArrayDynamic(VAO, VBO, NULL, sizeof(GLfloat) * 6 * 4);
		Graphics::EnableVertexArrayAttribute(0, 4, 4 * sizeof(GLfloat), 0);
	}

	void RenderQuad(int texID, Shader& shader, GLfloat _x,
		GLfloat _y, GLfloat _z, GLfloat _localx, GLfloat _localy,
		GLfloat scaleX, GLfloat scaleY,
		const glm::vec4& color)
	{
		Graphics::EnableTransparency(true);


		GLfloat camWidth = WINDOW_WIDTH;
		GLfloat camHeight = WINDOW_HEIGHT;

		GLfloat x = _x * camWidth + _localx;
		GLfloat y = _y * camHeight + _localy;

		glm::mat4 projection = glm::ortho(0.0f, camWidth, 0.0f, camHeight);
		GLfloat xpos = x;
		GLfloat ypos = y;
		GLfloat vertices[6][4] =
		{
			{-0.5f, 0.5f,0.0f,0.0f},
			{-0.5f, -0.5f,0.0f,1.0f},
			{0.5f, -0.5f, 1.0f, 1.0f},

			{-0.5f, 0.5f, 0.0f, 0.0f},
			{0.5f, -0.5f,1.0f,1.0f},
			{0.5f , 0.5f, 1.0f, 0.0f}
		};

		shader.UseShader();

		glm::mat4  temp{ 1.0f };
		glm::vec3 scalen = glm::vec3(scaleX, scaleY, 1.0f);
		glm::vec3 trans = glm::vec3(xpos, ypos, _z);

		temp = glm::translate(temp, trans);

		temp = glm::scale(temp, scalen);

		Graphics::UniformMat4(shader.GetModelLocation(), temp);
		Graphics::UniformMat4(shader.GetProjectionLocation(), projection);
		Graphics::UniformVec4(shader.GetColourLocation(), color);
		Graphics::SendTexture(texID, 0, shader.GetDiffuseLocation());
		Graphics::BindVertexSubBuffer(VBO, (float*)vertices, sizeof(vertices));

		Graphics::DrawTrianglesArray(VAO, 6);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
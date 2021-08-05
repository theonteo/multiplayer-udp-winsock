/*****************************************************************************/
/*!
\file Skybox.cpp

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
#include "Skybox.h"
#include "Texture.h"
#include "Resource.h"

/******************************************************************************/
/*!
\brief  use texture 
*/
/******************************************************************************/
void Skybox::UseTextureCubeMap() 
{
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
}
/******************************************************************************/
/*!
\brief  skybox constructor
*/
/******************************************************************************/
Skybox::Skybox(std::vector<std::string> faceLocations)
{
	// Shader Setup
//	skyShader = new Shader();
	skyShader="Shaders\\skybox";

	const auto& shader = Resource::Shader_List.find(skyShader)->second;


	uniformProjection = shader->GetProjectionLocation();
	uniformView = shader->GetViewLocation();

	// Texture Setup
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	for (size_t i = 0; i < 6; i++)
	{

		FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(faceLocations[i].c_str());
		FIBITMAP* ib = FreeImage_Load(fif, faceLocations[i].c_str(), JPEG_DEFAULT);
		FreeImage_FlipVertical(ib);
		int width = FreeImage_GetWidth(ib);
		int height = FreeImage_GetHeight(ib);
		
		if (!ib)
		{
			printf("Failed to find: %s\n", faceLocations[i].c_str());
			return;
		}

		glTexImage2D((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, GL_RGB, 
			width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(ib));
		FreeImage_Unload(ib);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mesh Setup
	unsigned int skyboxIndices[] = {
		// front
		0, 1, 2,
		2, 1, 3,
		// right
		2, 3, 5,
		5, 3, 7,
		// back
		5, 7, 4,
		4, 7, 6,
		// left
		4, 6, 0,
		0, 6, 1,
		// top
		4, 0, 5,
		5, 0, 2,
		// bottom
		1, 6, 3,
		3, 6, 7
	};

	float skyboxVertices[] = {
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,0.0f,		0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,0.0f,		0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f,0.0f,		0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f,0.0f,		0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,

		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,0.0f,		0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,0.0f,		0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,	0.0f,	0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f,0.0f,		0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f,0.0f, 0.0f, 0.0f
	};

	skyMesh = new Mesh();
	skyMesh->CreateMesh(skyboxVertices, skyboxIndices, 118, 36);
}

/******************************************************************************/
/*!
\brief  draw skybox
*/
/******************************************************************************/
void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	glDepthMask(GL_FALSE);
	const auto& shader = Resource::Shader_List.find(skyShader)->second;
	shader->UseShader();
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	skyMesh->RenderMesh();

	glDepthMask(GL_TRUE);
}

/******************************************************************************/
/*!
\file Skybox.h
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
This file contains the declarations of the skybox class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>

#include <GL\glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
class Skybox
{
public:
	Skybox(std::vector<std::string> faceLocations);
	Skybox() = default;
	void UseTextureCubeMap();
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

private:
	GLuint textureId;
	Mesh* skyMesh;
	std::string skyShader;
	GLuint uniformProjection, uniformView;
};

#endif

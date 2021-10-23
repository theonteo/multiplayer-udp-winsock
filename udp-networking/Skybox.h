/******************************************************************************/
/*!
\file Skybox.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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

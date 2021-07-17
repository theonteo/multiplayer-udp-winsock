/*****************************************************************************/
/*!
\file
\author
\par email:
\par DigiPen login:
\par Course: cs260
\par Assignment 4
\date

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/*****************************************************************************/

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
	Shader* skyShader;
	GLuint uniformProjection, uniformView;
};

#endif

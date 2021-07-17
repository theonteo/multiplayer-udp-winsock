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

#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include <vector>
#include <string>
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cstring>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <Shader.h>
#include <Texture.h>

class PostProcess
{

	unsigned int intermediateFBO;
	unsigned int framebuffer;
	unsigned int quadVAO, quadVBO;
	unsigned int textureColorbuffer;

public:
	GLuint GetFrameBuffer();
	void DrawScenePostProcessing();
	void DrawPostProcessing();
	void LoadPostProcessing();

};

#endif
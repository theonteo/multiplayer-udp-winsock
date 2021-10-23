/******************************************************************************/
/*!
\file PostProcess.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

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
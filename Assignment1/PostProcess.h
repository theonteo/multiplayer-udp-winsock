/******************************************************************************/
/*!
\file PostProcess.h
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
This file contains the declarations of the Post Processing Class used by the
Graphics Engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
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
/**************************************************************************** /
/*!
\file Render.h

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

#ifndef RENDER_H
#define RENDER_H

#include <glm.hpp>
#include <string>
class DirectionalLight;
class Shader;
class PostProcess;

class Render
{
	//render functions
	Render();
	static void RenderShadow();
	static void RenderAll();

public:

	//store shader pointers
	static std::string directionalShadowShader;
	static std::string SkyBoxShader;
	static std::string screenShader;
	static PostProcess postprocess;

	static void Init();

	//assign data
	static void AssignShaders();

	//main render pass
	static void DirectionalShadowPass
	(DirectionalLight* light);

	static void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
};

#endif
/******************************************************************************/
/*!
\file Render.h
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
This file contains the declarations of the rendering functions used by the
application.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

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
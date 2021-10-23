/******************************************************************************/
/*!
\file Render.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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
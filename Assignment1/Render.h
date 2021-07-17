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

#ifndef RENDER_H
#define RENDER_H

#include <glm.hpp>

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
	static Shader* directionalShadowShader;
	static Shader* SkyBoxShader;
	static Shader* screenShader;
	static PostProcess postprocess;

	static void Init();

	//assign data
	static void AssignRenderObject();
	static void AssignShaders();

	//main render pass
	static void DirectionalShadowPass(DirectionalLight* light, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	static void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
};

#endif
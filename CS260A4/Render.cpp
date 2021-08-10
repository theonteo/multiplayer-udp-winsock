/******************************************************************************/
/*!
\file Render.cpp
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
This file contains the definitions of the rendering functions used by the 
application.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "GameObjectManager.h"
#include "Render.h"
#include "Resource.h"
#include "Lighting.h"
#include "PostProcess.h"
#include "Camera.h"
#include "Skybox.h"
#include "Model.h"
#include "GameObject.h"
#include "glm.hpp"

//static declarations
static const float toRadians = 3.14159265f / 180.0f;

static GLuint uniformProjection = 0,
uniformModel = 0,
uniformView = 0,
uniformAmbientIntensity = 0,
uniformAmbientColour = 0,
uniformDiffuseIntensity = 0,
uniformDirection = 0,
uniformSpecularIntensity = 0,
uniformShininess = 0,
uniformEyePosition = 0;

PostProcess Render::postprocess;
std::string Render::directionalShadowShader;
std::string Render::SkyBoxShader;
std::string Render::screenShader;
std::string selected_shader;
std::string line_shader;

Skybox skybox1;


/******************************************************************************/
/*!
\brief initiate render
*/
/******************************************************************************/
void Render::Init()
{
	Render::AssignShaders();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Cubemaps/s_1.jpg");
	skyboxFaces.push_back("Cubemaps/s_2.jpg");
	skyboxFaces.push_back("Cubemaps/s_3.jpg");
	skyboxFaces.push_back("Cubemaps/s_4.jpg");
	skyboxFaces.push_back("Cubemaps/s_5.jpg");
	skyboxFaces.push_back("Cubemaps/s_6.jpg");
	skybox1 = Skybox(skyboxFaces);
}

/******************************************************************************/
/*!
\brief render shadows
*/
/******************************************************************************/
void Render::RenderShadow() 
{
	glm::mat4 model = glm::mat4(1.0f);
	for (auto& go :GameObjectManager::GameObjectList)
	{
		if (!go.second->enabled)continue;
		const std::unique_ptr<Shader>& shader = 
			Resource::Shader_List.find(directionalShadowShader)->second;

		model = glm::mat4(1.0f);
		model = glm::translate(model, go.second->translate);
		model = glm::rotate(model, go.second->rotation.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, go.second->rotation.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, go.second->rotation.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, go.second->scale);

		uniformModel = shader->GetModelLocation();

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Resource::Model_List.find(go.second->Model)->second->RenderModel();
	}
}

/******************************************************************************/
/*!
\brief  render all
*/
/******************************************************************************/
void Render::RenderAll() 
{
	glm::mat4 model = glm::mat4(1.0f);

	//default cubemap
	skybox1.UseTextureCubeMap();

	model = glm::mat4(1.0f);

	// run all gameobject
	for (auto& gos : GameObjectManager::GameObjectList)
	{
		if (!gos.second->enabled)continue;

		const std::unique_ptr<GameObject>& go = gos.second;

		const std::unique_ptr<Shader>& shader =
			Resource::Shader_List.find(go->shader)->second;

		selected_shader = go->shader;

		if (shader)  shader->UseShader();

		glUniform1f(uniformSpecularIntensity,2.0f);
		glUniform1f(uniformShininess, 25.0f);

		//diffuse colour
		glUniform3f(shader->GetColourLocation(),
			go->colour.x, go->colour.y, go->colour.z);

		model = glm::mat4(1.0f);
		model = glm::translate(model, go->translate);
		model = glm::rotate(model, go->rotation.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, go->rotation.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, go->rotation.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, go->scale);

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//render model
		Resource::Model_List.find(go->Model)->second->RenderModel();
	}
}
/******************************************************************************/
/*!
\brief  directional shadow pass
*/
/******************************************************************************/
void Render::DirectionalShadowPass
(DirectionalLight* light)
{
	const std::unique_ptr<Shader>& shader =
		Resource::Shader_List.find(directionalShadowShader)->second;

	shader->UseShader();
	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(),
		light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	shader->SetDirectionalLighttransform(light->CalculateLightTransform());

	RenderShadow();

}
/******************************************************************************/
/*!
\brief render pass
*/
/******************************************************************************/
void Render::RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	if (GameObjectManager::GameObjectList.empty())return;
	const std::unique_ptr<GameObject>& go = 
		GameObjectManager::GameObjectList.begin()->second;

	DirectionalShadowPass(&Lighting::mainLight);

	glBindFramebuffer(GL_FRAMEBUFFER, postprocess.GetFrameBuffer());
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(1.0f, 1.0f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const std::unique_ptr<Shader>& screenshader =
		Resource::Shader_List.find(screenShader)->second;

	screenshader->UseShader();
	screenshader->SetScreenTexture(10);

	selected_shader = go->shader;
	const std::unique_ptr<Shader>& shader =
		Resource::Shader_List.find(go->shader)->second;

	if (shader)
	{
		shader->UseShader();
		uniformModel = shader->GetModelLocation();
		uniformProjection =shader->GetProjectionLocation();
		uniformView = shader->GetViewLocation();
		uniformModel = shader->GetModelLocation();
		uniformEyePosition = shader->GetEyePositionLocation();
		uniformSpecularIntensity = shader->GetSpecularIntensityLocation();
		uniformShininess = shader->GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniform3f
		(uniformEyePosition, Resource::camera->getCameraPosition().x,
			Resource::camera->getCameraPosition().y, Resource::camera->getCameraPosition().z);

		shader->SetDirectionalLight(&Lighting::mainLight);
		shader->SetPointLight(Lighting::pointLights, Lighting::pointLightCount);
		shader->SetSpotLight(Lighting::spotLights, Lighting::spotLightCount);
		shader->SetDirectionalLighttransform(Lighting::mainLight.CalculateLightTransform());
		Lighting::mainLight.GetShadowMap()->Read(GL_TEXTURE1);

		shader->SetTexture(0);
		shader->SetDirectionalShadowMap(1);
		shader->SetTextureNormal(2);
		shader->SetTextureCubeMap(6);
	}

	skybox1.DrawSkybox(viewMatrix, projectionMatrix);

	//render all objects
	RenderAll();

	//render normal
	if (Resource::enableNormal)
	{

		const std::unique_ptr<Shader>& lineshader =
			Resource::Shader_List.find(line_shader)->second;

		//use line shader
		lineshader->UseShader();

		//set matrix
		uniformModel = lineshader->GetModelLocation();
		uniformProjection = lineshader->GetProjectionLocation();
		uniformView = lineshader->GetViewLocation();

		//set model matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, go->translate);
		model = glm::rotate(model, go->rotation.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, go->rotation.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, go->rotation.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, go->scale);

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		Resource::Model_List.find(go->Model)->second->RenderNormals();
	}

	Lighting::mainLight.SetLightRotation(Resource::directionalRotation);

	//draw frame buffer
	screenshader->UseShader();
	postprocess.DrawPostProcessing();

}
/******************************************************************************/
/*!
\brief  assign render shaders
*/
/******************************************************************************/
void Render::AssignShaders()
{
	directionalShadowShader = "Shaders\\directional_shadow_map";
	SkyBoxShader = "Shaders\\skybox";
	screenShader = "Shaders\\framebuffers_screen";
	line_shader ="Shaders\\shader_line";
}


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
Shader* Render::directionalShadowShader;
Shader* Render::SkyBoxShader;
Shader* Render::screenShader;

Skybox skybox1;
Shader* selected_shader;
Shader* line_shader;
GameObject go;

/******************************************************************************/
/*!
\brief initiate render
*/
/******************************************************************************/
void Render::Init()
{
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
	for (auto& go : Resource::GameObject_List)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, go.second->translate);
		model = glm::rotate(model, go.second->rotation.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, go.second->rotation.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, go.second->rotation.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, go.second->scale);

		uniformModel = directionalShadowShader->GetModelLocation();

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		go.second->Model->RenderModel();
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

	for (auto& gos : Resource::GameObject_List)
	{
		GameObject* go = gos.second;

		selected_shader = go->shader;

		if (selected_shader)  selected_shader->UseShader();

		glUniform1f(uniformSpecularIntensity,2.0f);
		glUniform1f(uniformShininess, 25.0f);

		model = glm::mat4(1.0f);
		model = glm::translate(model, go->translate);
		model = glm::rotate(model, go->rotation.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, go->rotation.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, go->rotation.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, go->scale);

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//render model
		go->Model->RenderModel();

	}
}

/******************************************************************************/
/*!
\brief  directional shadow pass
*/
/******************************************************************************/
void Render::DirectionalShadowPass
(DirectionalLight* light, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{

	directionalShadowShader->UseShader();
	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	directionalShadowShader->SetDirectionalLighttransform(&light->CalculateLightTransform());

	RenderShadow();

}
/******************************************************************************/
/*!
\brief render pass
*/
/******************************************************************************/
void Render::RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{

	DirectionalShadowPass(&Lighting::mainLight, viewMatrix, projectionMatrix);


	glBindFramebuffer(GL_FRAMEBUFFER, postprocess.GetFrameBuffer());
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(1.0f, 1.0f, 0.75f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	screenShader->UseShader();
	screenShader->SetScreenTexture(10);

	selected_shader = go.shader;

	if (selected_shader)
	{
		selected_shader->UseShader();
		uniformModel = selected_shader->GetModelLocation();
		uniformProjection = selected_shader->GetProjectionLocation();
		uniformView = selected_shader->GetViewLocation();
		uniformModel = selected_shader->GetModelLocation();
		uniformEyePosition = selected_shader->GetEyePositionLocation();
		uniformSpecularIntensity = selected_shader->GetSpecularIntensityLocation();
		uniformShininess = selected_shader->GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniform3f
		(uniformEyePosition, Resource::camera->getCameraPosition().x,
			Resource::camera->getCameraPosition().y, Resource::camera->getCameraPosition().z);

		selected_shader->SetDirectionalLight(&Lighting::mainLight);
		selected_shader->SetPointLight(Lighting::pointLights, Lighting::pointLightCount);
		selected_shader->SetSpotLight(Lighting::spotLights, Lighting::spotLightCount);
		selected_shader->SetDirectionalLighttransform(&Lighting::mainLight.CalculateLightTransform());
		Lighting::mainLight.GetShadowMap()->Read(GL_TEXTURE1);

		selected_shader->SetTexture(0);
		selected_shader->SetDirectionalShadowMap(1);
		selected_shader->SetTextureNormal(2);
		selected_shader->SetTextureCubeMap(6);
	}

	skybox1.DrawSkybox(viewMatrix, projectionMatrix);

	//render all objects
	RenderAll();

	//render normal
	if (Resource::enableNormal)
	{
		//use line shader
		line_shader->UseShader();

		//set matrix
		uniformModel = line_shader->GetModelLocation();
		uniformProjection = line_shader->GetProjectionLocation();
		uniformView = line_shader->GetViewLocation();

		//set model matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, go.translate);
		model = glm::rotate(model, go.rotation.x * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, go.rotation.y * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, go.rotation.z * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, go.scale);

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		go.Model->RenderNormals();
	}

	Lighting::mainLight.SetLightRotation(Resource::directionalRotation);

	//draw frame buffer
	screenShader->UseShader();
	postprocess.DrawPostProcessing();

}
/******************************************************************************/
/*!
\brief  assign render shaders
*/
/******************************************************************************/
void Render::AssignShaders()
{
	directionalShadowShader = (*Resource::Shader_List.find("Shaders\\directional_shadow_map")).second;
	SkyBoxShader = (*Resource::Shader_List.find("Shaders\\skybox")).second;
	screenShader = (*Resource::Shader_List.find("Shaders\\framebuffers_screen")).second;
	line_shader = (*Resource::Shader_List.find("Shaders\\shader_line")).second;
}

/******************************************************************************/
/*!
\brief  assign render objects
*/
/******************************************************************************/
void Render::AssignRenderObject() 
{
	//set initial object
	go.translate = glm::vec3(0.0f, 0.0f, 0.0f);
	go.rotation = glm::vec3(0, 0, 0);
	go.scale = glm::vec3(1, 1, 1);
	go.GameObjectName = "Main Object";
	
	go.Model = (*Resource::Model_List.find("Models\\cube.obj")).second;
	go.shader = (*Resource::Shader_List.find("Shaders\\shader_vertex")).second;
	Resource::GameObject_List.insert(std::pair<std::string, GameObject*>("Main Object", &go));
}

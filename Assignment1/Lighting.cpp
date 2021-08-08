/******************************************************************************/
/*!
\file Lighting.cpp
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
This file contains the definitions of the lighting class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "Lighting.h"
#include "Resource.h"


//light declaration
PointLight Lighting::pointLights[MAX_POINT_LIGHTS];
SpotLight Lighting::spotLights[MAX_SPOT_LIGHTS];
DirectionalLight Lighting::mainLight;

unsigned int Lighting::pointLightCount = 0;
unsigned int Lighting::spotLightCount = 0;

void Lighting::UpdatePointLight
(int index,const glm::vec3& col, const glm::vec3& pos, float intensity)
{
	pointLights[index].SetIntensity(intensity);
	pointLights[index].SetColour(col);
	pointLights[index].SetPosition(pos);
}

/******************************************************************************/
/*!
\brief  lighting init - hardcoded values for now
*/
/******************************************************************************/
void Lighting::init()
{
	Resource::directionalRotation = glm::vec3(225.0f, -25.0f, 0.0f);
	mainLight = DirectionalLight(
		4096, 4096,
		0.2f,0.2f, 0.25f,
		0.f, 1.15f,
		225.0f, -25.0f, 0.0f);

	pointLights[0] =
		PointLight(
			1024, 1024,
			1.0f, 1.0f, 1.0f,
			0.1f, 0.0f,
			-5.2f, -10.0f, 0.0f,
			0.3f, 0.2f,0.1f);
	pointLightCount++;

	pointLights[1] =
		PointLight(
			1024, 1024,
			1.0f, 1.0f, 1.0f,
			0.1f, 0.0f,
			3.1f, -10.0f, -2.1f,
			0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[2] =
		PointLight(
			1024, 1024,
			1.0f,1.0f, 1.0f,
			0.1f, 0.0f,
			3.1f, -10.0f, -2.1f,
			0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[3] =
		PointLight(
			1024, 1024,
			1.0f, 1.0f, 1.0f,
			0.1f, 0.0f,
			3.1f, -10.0f, -2.1f,
			0.3f, 0.2f, 0.1f);
	pointLightCount++;

	spotLights[0] =
		SpotLight(
			1024, 1024,
			0.0f, 0.0f, 0.0f,
			0.1f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.3f, 0.2f, 0.1f,
			35.0f);
	spotLightCount++;

	spotLights[1] =
		SpotLight(
			1024, 1024,
			0.0f, 0.0f, 0.0f,
			0.1f, 0.0f,
			0.0f, 0.0f, 0.0f,
			30.0f, -1.0f, 0.0f,
			0.3f, 0.2f, 0.1f,
			35.0f);
	spotLightCount++;


	Resource::Light_List.insert(std::pair <std::string, Light*>("Point Light 1", &pointLights[0]));
	Resource::Light_List.insert(std::pair <std::string, Light*>("Point Light 2", &pointLights[1]));
	Resource::Light_List.insert(std::pair <std::string, Light*>("Point Light 3", &pointLights[2]));
	Resource::Light_List.insert(std::pair <std::string, Light*>("Spot Light 1", &spotLights[0]));
	Resource::Light_List.insert(std::pair <std::string, Light*>("Spot Light 2", &spotLights[1]));

}

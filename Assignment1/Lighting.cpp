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

#include "Lighting.h"
#include "Resource.h"
#include "CommonValues.h"

//light declaration
PointLight Lighting::pointLights[MAX_POINT_LIGHTS];
SpotLight Lighting::spotLights[MAX_SPOT_LIGHTS];
DirectionalLight Lighting::mainLight;

unsigned int Lighting::pointLightCount = 0;
unsigned int Lighting::spotLightCount = 0;


/******************************************************************************/
/*!
\brief  lighting init - hardcoded values for now
*/
/******************************************************************************/
void Lighting::init()
{

	mainLight = DirectionalLight(
		4096, 4096,
		0.05f,0.01f, 0.0f,
		0.25f, 1.15f,
		45.0f, 15.0f, 10.0f);

	pointLights[0] =
		PointLight(
			1024, 1024,
			1.0f, 1.0f, 1.0f,
			0.1f, 0.4f,
			-5.2f, 0.0f, 0.0f,
			0.3f, 0.2f,0.1f);
	pointLightCount++;

	pointLights[1] =
		PointLight(
			1024, 1024,
			1.0f, 1.0f, 1.0f,
			0.1f, 0.9f,
			3.1f, 1.0f, -2.1f,
			0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[2] =
		PointLight(
			1024, 1024,
			1.0f,1.0f, 1.0f,
			0.1f, 1.0f,
			3.1f, 1.0f, -2.1f,
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

/******************************************************************************/
/*!
\file Lighting.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef LIGHTING_H
#define LIGHTING_H
#include "CommonValues.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

class Lighting
{
public:

	static PointLight pointLights[MAX_POINT_LIGHTS];
	static SpotLight spotLights[MAX_SPOT_LIGHTS];
	static DirectionalLight mainLight;

	static unsigned int pointLightCount;
	static unsigned int spotLightCount;

	static void UpdatePointLight(int index, const glm::vec3& col, const glm::vec3& pos,float intensity);
	static void init();
};

#endif
/*****************************************************************************/
/*!
\file Lighting.h

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
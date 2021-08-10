/******************************************************************************/
/*!
\file Lighting.h
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
This file contains the declarations of the mesh class used by the graphics
engine.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
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
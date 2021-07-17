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

#ifndef LIGHTING_H
#define LIGHTING_H

#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"

class Lighting
{
public:

	static PointLight pointLights[3];
	static SpotLight spotLights[3];
	static DirectionalLight mainLight;

	static unsigned int pointLightCount;
	static unsigned int spotLightCount;

	static void init();
};

#endif
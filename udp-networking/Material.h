/******************************************************************************/
/*!
\file Material.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "glm.hpp"

class Material
{
public:

	void UseMaterial();

	Texture* TextureDiffuseTexture;
	Texture* TextureNormalTexture;

	GLfloat specularIntensity;
	GLfloat shininess;
};

#endif
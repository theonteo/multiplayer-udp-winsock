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
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

#include "Material.h"

/******************************************************************************/
/*!
\brief  use material - hard code for now
*/
/******************************************************************************/
void Material::UseMaterial()
{
		specularIntensity = 2.00f;
		shininess = 25.0f;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureDiffuseTexture->textureID);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, TextureNormalTexture->textureID);
}



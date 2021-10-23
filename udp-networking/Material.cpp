/******************************************************************************/
/*!
\file Material.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

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



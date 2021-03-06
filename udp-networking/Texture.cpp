/******************************************************************************/
/*!
\file Texture.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#include "Texture.h"

/******************************************************************************/
/*!
\brief  texture constructor
*/
/******************************************************************************/
Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}
/******************************************************************************/
/*!
\brief  texture constructor
*/
/******************************************************************************/
Texture::Texture(const char* fileLoc)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileLoc;
	filename = fileLoc;
	LoadTexture();
}
/******************************************************************************/
/*!
\brief  load texture
*/
/******************************************************************************/
bool Texture::LoadTexture()
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(fileLocation);
	FIBITMAP* ib = FreeImage_Load(fif, fileLocation, PNG_DEFAULT);
	FreeImage_FlipVertical(ib);
	int w = FreeImage_GetWidth(ib);
	int h = FreeImage_GetHeight(ib);

	if (!ib)
	{
		printf("Fail to find:%sn", fileLocation);
		return false;
	}
	else {
		printf("Loaded:%s\n", fileLocation);
	}
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h,
		0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(ib));
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	FreeImage_Unload(ib);
	return true;
}
/******************************************************************************/
/*!
\brief  clear texture
*/
/******************************************************************************/
void Texture::ClearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}
/******************************************************************************/
/*!
\brief use diffuse
*/
/******************************************************************************/
void Texture::UseTextureDiffuse()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

}
/******************************************************************************/
/*!
\brief  use normal
*/
/******************************************************************************/
void Texture::UseTextureNormal() 
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureID);

}

/******************************************************************************/
/*!
\brief  show location text
*/
/******************************************************************************/
void Texture::showloc()
{
	ImGui::Text(fileLocation);
}
/******************************************************************************/
/*!
\brief  destructor
*/
/******************************************************************************/
Texture::~Texture()
{
	ClearTexture();
}

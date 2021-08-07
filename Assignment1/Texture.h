/*****************************************************************************/
/*!
\file Texture.h
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

#ifndef TEXTURE_H
#define TEXTURE_H
#include <FreeImage.h>

#include <GL\glew.h>
#include <stdio.h>
#include <cstring> 
#include <imgui.h>
#include<iostream>

class Texture
{
public:
	Texture();
	Texture(const char*fileLoc);

	bool LoadTexture();
	void ClearTexture();
	void UseTextureDiffuse();
	void UseTextureNormal();
	void showloc();

	//private:

	std::string filename;

	int width, height, bitDepth;
	GLuint textureID;
	const char* fileLocation;

	~Texture();
};

#endif
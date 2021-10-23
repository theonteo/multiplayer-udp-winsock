/******************************************************************************/
/*!
\file Texture.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

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
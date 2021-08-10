/******************************************************************************/
/*!
\file Texture.h
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
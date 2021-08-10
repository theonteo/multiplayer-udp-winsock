/******************************************************************************/
/*!
\file Resource.h
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
This file contains the declarations of the resource functions used by the
application.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/
#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>
#include <filesystem>
#include <map>
#include <glm.hpp>

class Camera;
class Light;
class Texture;
class Model;
class Material;
class GameObject;
class Shader;


class Resource
{
public:

	//store data

	static std::map<std::string, std::unique_ptr<Texture>>Texture_List;
	static std::map<std::string, std::unique_ptr<Shader>>Shader_List;
	static std::map<std::string, std::unique_ptr<Material>>Material_List;
	static std::map<std::string, std::unique_ptr<Model>>Model_List;
	static std::map<std::string, Light*>Light_List;

	static Texture* Texture_Selected;
	static Material* Material_Selected;

	//editor options
	static bool enableNormal;
	static bool fragmentLighting;

	//load functions
	void loadFiles();

	//static variables
	static glm::vec3 directionalRotation;
	static Camera* camera;

private:
	//load models
	void FileLoad_Models();

	//load skinned models
	void FileLoad_Textures();

	//load shader
	void FileLoad_Shaders();

	//path data
	std::string pathString;
	std::string pathName;
	std::vector<std::filesystem::path> allpaths;
	std::string pathextension;
	std::filesystem::path path;
	std::string mainpath;
};
#endif

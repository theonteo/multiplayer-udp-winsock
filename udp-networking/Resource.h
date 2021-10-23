/******************************************************************************/
/*!
\file Resource.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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

/******************************************************************************/
/*!
\file Resource.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#include "Resource.h"
#include "glm.hpp"
#include <Texture.h>
#include <Material.h>
#include <Shader.h>
#include "Model.h"

//static declaration
bool Resource::enableNormal = false;
bool Resource::fragmentLighting = false;
Texture* Resource::Texture_Selected;
Material* Resource::Material_Selected;
Camera* Resource::camera;


std::map<std::string, std::unique_ptr<Shader>>Resource::Shader_List;
std::map<std::string, std::unique_ptr<Material>>Resource::Material_List;
std::map<std::string, std::unique_ptr<Model>>Resource::Model_List;
std::map<std::string, std::unique_ptr<Texture>>Resource::Texture_List;
std::map<std::string, Light*>Resource::Light_List;

glm::vec3 Resource::directionalRotation;

/******************************************************************************/
/*!
\brief   create path name from string
*/
/******************************************************************************/
std::string CreatePathName(std::string pathname)
{
	std::string cus = std::filesystem::current_path().string();
	return cus.append("\\" + pathname);
}

/******************************************************************************/
/*!
\brief   reformat path name for loading
*/
/******************************************************************************/
std::string PathReformat(std::string path, std::string _pathextension)
{
	//reformats the path needed for respective classes to run
	std::string temp = path;
	const size_t last_slash_idx = temp.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		temp.erase(0, last_slash_idx + 1);
	}
	std::string temp2 = _pathextension;
	temp2.append("\\" + temp);
	return temp2;
}

/******************************************************************************/
/*!
\brief   reformat path name and type name for loading
*/
/******************************************************************************/
std::string PathReformatTypeName(std::string _path, std::string _pathextension)
{
	//Reformats the string and exclude the file type
	std::string temp = _path;
	const size_t last_slash_idx = temp.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
		temp.erase(0, last_slash_idx + 1);

	const size_t period_idx = temp.find('.');

	if (std::string::npos != period_idx)
		temp.erase(period_idx);

	std::string temp2 = _pathextension;
	return temp2.append("\\" + temp);
}
/******************************************************************************/
/*!
\brief  load all files
*/
/******************************************************************************/
void Resource::loadFiles()
{
	Resource::Texture_Selected = NULL;
	Resource::Material_Selected = NULL;

	allpaths.clear();

	FileLoad_Models();
	FileLoad_Textures();

	FileLoad_Shaders();
}

/******************************************************************************/
/*!
\brief   load models
*/
/******************************************************************************/
void Resource::FileLoad_Models()
{

	//load models
	pathextension = CreatePathName("Models");

	for (const auto& entry : std::filesystem::directory_iterator(pathextension))
	{

		pathString = PathReformat(entry.path().string(), "Models");
		Model* model_new = new Model();
		pathName = pathString;
		model_new->ModelName = pathString;
		Model_List.insert(std::pair<std::string, Model*>(pathString, model_new));
	}
	//load all Models
	for (const auto& i : Resource::Model_List)
		i.second->LoadAssetModel(i.second->ModelName);

}
/******************************************************************************/
/*!
\brief  load textures
*/
/******************************************************************************/
void Resource::FileLoad_Textures()
{
	pathextension = CreatePathName("Textures");

	// load all textures in files
	for (auto& entry : std::filesystem::directory_iterator(pathextension))
	{
		// get path string
		pathString = PathReformat(entry.path().string(), "Textures");

		// create texture
		Texture* texture = new Texture(pathString.c_str());

		Resource::Texture_List.insert(std::pair<std::string, Texture*>(pathString.c_str(), texture));
	}
}

/******************************************************************************/
/*!
\brief  load shaders
*/
/******************************************************************************/
void Resource::FileLoad_Shaders()
{
	pathextension = CreatePathName("Shaders");
	bool t = false;
	for (auto& entry : std::filesystem::directory_iterator(pathextension))
	{
		if (t == false)
		{
			t = true;
			std::string shader_name = PathReformatTypeName(entry.path().string(), "Shaders");

			std::string shader_vert = shader_name;
			std::string shader_frag = shader_name;
			shader_vert.append(".vert");
			shader_frag.append(".frag");

			std::unique_ptr<Shader> shader_new = std::make_unique<Shader>();

			shader_new->CreateFromFiles(shader_vert.c_str(), shader_frag.c_str());
			std::cout << "Loaded vert: " << shader_vert << ", frag: " << shader_frag << std::endl;
			shader_new->shaderName = shader_name;
			Shader_List.insert(std::pair<std::string, std::unique_ptr<Shader>>(shader_new->shaderName, std::move(shader_new)));

		}
		else
		{
			t = false;
		}
	}
}


/*****************************************************************************/
/*!
\file GameObject.h

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

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm.hpp>

class Model;
class Shader;
class Material;

class GameObject
{
public:

	//store pointers to data
	std::string GameObjectMaterial;
	std::string Model;
	std::string shader;

	int score{ 0 };

	bool enabled{ true };

	unsigned char direction; // Bool flag

	//store transforms
	glm::vec3 translate = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(0, 0, 0);
	glm::vec3 colour = glm::vec3(1, 1, 1);

	std::string GameObjectName;
};
#endif

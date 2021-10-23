/******************************************************************************/
/*!
\file GameObject.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

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

	int score{ -1 };

	bool enabled{ true };

	unsigned char direction; // Bool flag

	//store transforms
	glm::vec3 translate = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(0, 0, 0);
	glm::vec3 colour = glm::vec3(1, 1, 1);
	glm::vec3 point1 = glm::vec3(0, 0, 0);
	glm::vec3 point2 = glm::vec3(0, 0, 0);

	glm::vec3 clientPos = glm::vec3(0, 0, 0);
	glm::vec3 clientVel = glm::vec3(0, 0, 0);
	glm::vec3 serverPos = glm::vec3(0, 0, 0);
	glm::vec3 serverVel = glm::vec3(0, 0, 0);

	float counter = 0.0f;

	std::string GameObjectName;
};
#endif

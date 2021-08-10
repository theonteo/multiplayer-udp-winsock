/******************************************************************************/
/*!
\file Camera.h
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
This file contains the declarations of the game camera class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include <string> 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <gtc/matrix_transform.hpp>
#include <glm.hpp>

class Interface;

class Camera
{

private:
	friend Interface;
	glm::mat4 projection{};

	glm::vec3 position{};
	glm::vec3 front{};
	glm::vec3 up{};
	glm::vec3 right{};
	glm::vec3 worldUp{};

	GLfloat fov{};
	GLfloat nearPlane{};
	GLfloat farPlane{};

	GLfloat yaw{};
	GLfloat pitch{};
	GLfloat moveSpeed{};
	GLfloat turnSpeed{};

	std::string lookTarget;

	void update();

public:
	Camera() = default;
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw,
		GLfloat startPitch, GLfloat startMovespeed, GLfloat startTurnspeed);
	
	//controls
	void keyControl(bool* keys,GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::mat4 calculateViewMatrix();
	glm::mat4 calculateProjectionMatrix(GLfloat aspect);
	glm::vec3 getCameraPosition();
	glm::vec2 getCameraRotation();

	void SetPosition(const glm::vec3& pos);
	void SetRotation(const glm::vec2& rot);

	//getters
	GLfloat getFov();
	GLfloat getNearPlane();
	GLfloat getFarPlane();
};

#endif


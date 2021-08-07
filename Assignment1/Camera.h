/*****************************************************************************/
/*!
\file Camera.h

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


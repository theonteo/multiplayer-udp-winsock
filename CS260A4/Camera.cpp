/******************************************************************************/
/*!
\file Camera.cpp
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
This file contains the definitions of the game camera class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "Camera.h"

/******************************************************************************/
/*!
\brief  constructor
*/
/******************************************************************************/
Camera::Camera
(glm::vec3 startPosition, glm::vec3 startUp,
	GLfloat startYaw, GLfloat startPitch, 
	GLfloat startMovespeed, GLfloat startTurnspeed)
{
	fov = 85.0f;
	nearPlane = 0.1f;
	farPlane = 1000.0f;

	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	moveSpeed = startMovespeed;
	turnSpeed = startTurnspeed;
	update();
}

/******************************************************************************/
/*!
\brief  key control
*/
/******************************************************************************/
void Camera::keyControl(bool* keys, GLfloat deltaTime) 
{
	(void)deltaTime;
	(void)keys;
}

/******************************************************************************/
/*!
\brief  mouse control
*/
/******************************************************************************/
void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;
	if (pitch > 80.0f)		
		pitch = 80.0f;
	if (pitch < -80.0f)
		pitch = -80.0f;

	update();
}

/******************************************************************************/
/*!
\brief  calculate view matrix
*/
/******************************************************************************/
glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}
glm::mat4 Camera::calculateProjectionMatrix(GLfloat aspect)
{
	return glm::perspective(glm::radians(fov), aspect,nearPlane,farPlane);
}

/******************************************************************************/
/*!
\brief  get camera position
*/
/******************************************************************************/
glm::vec3 Camera::getCameraPosition() 
{
	return position;
}

glm::vec2 Camera::getCameraRotation()
{
	return { pitch,yaw };
}

void Camera::SetPosition(const glm::vec3& pos)
{
	position = pos;
}
void Camera::SetRotation(const glm::vec2& rot)
{
	pitch = rot.x;
	yaw = rot.y;
}

/******************************************************************************/
/*!
\brief get field of view
*/
/******************************************************************************/
GLfloat Camera::getFov()
{
	return fov;
}

/******************************************************************************/
/*!
\brief get near plane
*/
/******************************************************************************/
GLfloat Camera::getNearPlane()
{
	return nearPlane;
}

/******************************************************************************/
/*!
\brief  get far plane
*/
/******************************************************************************/
GLfloat Camera::getFarPlane()
{
	return farPlane;
}

/******************************************************************************/
/*!
\brief  update camera
*/
/******************************************************************************/
void Camera::update() 
{

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


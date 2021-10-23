/******************************************************************************/
/*!
\file Camera.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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


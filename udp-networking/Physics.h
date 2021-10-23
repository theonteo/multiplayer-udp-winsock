/******************************************************************************/
/*!
\file Physics.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#pragma once
#include <glm.hpp>
namespace Physics
{
	bool CircleToCircle
	(const glm::vec3 pos1, float r1, const glm::vec3 pos2, float r2);
};


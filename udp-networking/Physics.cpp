/******************************************************************************/
/*!
\file Physics.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#include "Physics.h"

bool Physics::CircleToCircle
(const glm::vec3 pos1, float r1, const glm::vec3 pos2, float r2)
{
	return (glm::length(pos1 - pos2) < (r1 + r2));
}

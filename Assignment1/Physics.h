/*****************************************************************************/
/*!
\file Physics.h

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

#pragma once
#include <glm.hpp>
namespace Physics
{
	bool CircleToCircle
	(const glm::vec3 pos1, float r1, const glm::vec3 pos2, float r2);
};


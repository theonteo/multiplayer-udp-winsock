/*****************************************************************************/
/*!
\file Colors.h

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

#ifndef COLORS_H
#define COLORS_H

#include <vector>
#include <glm.hpp>

//default player colours
const std::vector<glm::vec3>	col({
	//blue
	{ 0.0f / 255.0f,191.0f / 255.0f, 255.0f / 255.0f},
	//red
	{255.0f / 255.0f,0.0f / 255.0f, 75.0f / 255.0f},
	//green
	{ 174.0f / 255.0f, 255.0f / 255.0f,0.0f / 255.0f},
	//orange
	{ 255.0f / 255.0f, 150.0f / 255.0f, 0.0f / 255.0f},
	});
#endif
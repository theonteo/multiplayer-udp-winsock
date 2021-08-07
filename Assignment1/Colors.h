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

#include <map>
#include <glm.hpp>

//default player colours
const std::map<std::string,glm::vec3>	col({
	//blue
	{"Player 1",{ 0.0f / 255.0f,191.0f / 255.0f, 255.0f / 255.0f}},
	//red
	{"Player 2",{255.0f / 255.0f,0.0f / 255.0f, 75.0f / 255.0f}},
	//green
	{"Player 3",{ 174.0f / 255.0f, 255.0f / 255.0f,0.0f / 255.0f}},
	//orange
	{"Player 4",{ 255.0f / 255.0f, 150.0f / 255.0f, 0.0f / 255.0f}},
	});
#endif
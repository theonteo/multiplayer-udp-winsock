/******************************************************************************/
/*!
\file Colors.h
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
This file contains the player's corresponding colours.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

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
/******************************************************************************/
/*!
\file Colors.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#ifndef COLORS_H
#define COLORS_H

#include <map>
#include <glm.hpp>

//default player colours
const std::map<std::string,glm::vec3>	colors({
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
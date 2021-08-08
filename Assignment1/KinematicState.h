/*****************************************************************************/
/*!
\file KinematicState.h

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

#ifndef KINEMATICSTATE_H
#define KINEMATICSTATE_H

#include <glm.hpp>

class KinematicState
{
public:
	glm::vec3 translate = glm::vec3(0, 0, 0);
	glm::vec3 velocity = glm::vec3(0, 0, 0);
};


#endif
/******************************************************************************/
/*!
\file Player.cpp
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
This file contains the definitions of the Player class.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "Player.h"

float Player::GetAveragePing()
{
	float result = 0.0f;

	for (const auto& pingData : latestPings)
	{
		std::chrono::duration<double> diff = pingData.end - pingData.start;
		result += static_cast<float>(diff.count());
	}
	
	result /= PING_ARRAY_SIZE;

	return result;
}

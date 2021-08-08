/*****************************************************************************/
/*!
\file Player.cpp

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

#include "Player.h"

float Player::GetAveragePing()
{
	float result = 0.0f;

	for (const auto& pingData : latestPings)
	{
		std::chrono::duration<double> diff = pingData.end - pingData.start;
		result += diff.count();
	}
	
	result /= PING_ARRAY_SIZE;

	return result;
}

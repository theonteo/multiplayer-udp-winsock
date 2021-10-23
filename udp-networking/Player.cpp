/******************************************************************************/
/*!
\file Player.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

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

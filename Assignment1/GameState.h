/*****************************************************************************/
/*!
\file GameState.h

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


class GameState
{

public:
	enum class State
	{
		STATE_LOBBY,
		STATE_GAMEPLAY,
		STATE_RESULTS,
		STATE_UNKNOWN
	};
	static State GetCurrentState();
	static void AppendState();
	static void SetState(const State& state);

private:

	static State currentState;

};


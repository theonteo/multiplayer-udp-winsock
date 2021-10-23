/******************************************************************************/
/*!
\file GameState.h
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/
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


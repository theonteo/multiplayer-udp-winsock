/******************************************************************************/
/*!
\file GameState.cpp
\author Choo Chi Keong Bryan
\author Kevin Hartono
\author Teo Zheng Yong Theon

\date 01/08/2021
\brief
This file contains the definition of the multiplayer udp c++ application.

*/
/******************************************************************************/

#include "GameState.h"

GameState::State GameState::currentState{ State::STATE_LOBBY };

GameState::State GameState::GetCurrentState()
{
	return currentState;
}

void GameState::AppendState()
{
	currentState = 
		static_cast<State>(static_cast<int>(currentState) + 1);

	if (currentState == State::STATE_UNKNOWN)
		currentState = State::STATE_LOBBY;
}

void GameState::SetState(const State& state)
{
	currentState = state;
}

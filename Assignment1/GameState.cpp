/*****************************************************************************/
/*!
\file GameState.cpp

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

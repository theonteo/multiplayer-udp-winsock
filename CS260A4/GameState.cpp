/******************************************************************************/
/*!
\file GameState.cpp
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
This file contains the definitions of the Game State class. That controls the 
game state.

Hours spent on this assignment: 100
Specific portions that gave you the most trouble: Network.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
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

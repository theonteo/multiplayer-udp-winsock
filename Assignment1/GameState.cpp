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

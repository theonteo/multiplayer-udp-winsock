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

private:

	static State currentState;

};


#pragma once
class GameFlow
{

	enum class Flow
	{
		FLOW_LOBBY,
		FLOW_GAMEPLAY,
		FLOW_RESULTS
	};

	Flow currentFlow{ Flow::FLOW_LOBBY };



};


#pragma once
#include "UDP.h"
class UDPReceive :
	public UDP
{

public:
	void Receive();
	void StartUp() override;
};


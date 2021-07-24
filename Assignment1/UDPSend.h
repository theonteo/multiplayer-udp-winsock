#pragma once
#include "UDP.h"
class UDPSend :
	public UDP
{

public:
	void Send();
	void StartUp() override;
};


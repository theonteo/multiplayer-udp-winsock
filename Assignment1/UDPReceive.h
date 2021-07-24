#pragma once
#include "UDP.h"
class UDPReceive :
	public UDP
{

public:
	void Receive();
	void StartUp(const std::string& port) override;
};


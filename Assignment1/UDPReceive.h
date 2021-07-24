#pragma once
#include "UDP.h"

struct Packet;

class UDPReceive :
	public UDP
{

public:
	Packet Receive();
	void StartUp(const std::string& port) override;
};


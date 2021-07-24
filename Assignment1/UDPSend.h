#pragma once
#include "UDP.h"

struct Packet;

class UDPSend :
	public UDP
{

public:
	void Send(const Packet& packet);
	void StartUp(const std::string& port) override;
};


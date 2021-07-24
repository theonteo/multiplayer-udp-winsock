#pragma once
#include "UDP.h"

struct Packet;

class UDPSend :
	public UDP
{

public:
	void Send(const Packet& packet);
	void StartUp() override;
};


#ifndef CLIENTPROCEDURES_H
#define CLIENTPROCEDURES_H

#define _WINSOCKAPI_ 
#pragma once
#include <winsock2.h>
#include <Windows.h>

#include "ClientNetwork.h"
#include "NetworkData.h"
#include "TextView.h"
#include "Form1.h"

class ClientProcedures
{
public:
	ClientNetwork* network;
	char network_data[MAX_PACKET_SIZE];

	ClientProcedures(void);
	~ClientProcedures(void);

	void sendInitPacket();
	void sendMessagePacket(char[]);
	void sendGamePacket(int, int, int, int);

	Packet update();
};

#endif
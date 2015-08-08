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
	ClientProcedures(void);
	~ClientProcedures(void);

	ClientNetwork* network;

	void sendActionPackets(char[]);

	char network_data[MAX_PACKET_SIZE];

	char* update();

};

#endif
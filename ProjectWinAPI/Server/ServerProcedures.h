#pragma once

#include <ctime>

#include "ServerNetwork.h"
#include "NetworkData.h"

class ServerProcedures
{

public:

	ServerProcedures(void);
	~ServerProcedures(void);

	void update();

	void receiveFromClients();

	void sendInitPacket();
	void sendStartGamePackets();
	void sendMessagePackets(char[],int);
	void sendGamePackets(int,int,int,int,int);

private:

	// IDs for the clients connecting for table in ServerNetwork 
	static unsigned int client_id;

	// The ServerNetwork object 
	ServerNetwork* network;

	// data buffer
	char network_data[MAX_PACKET_SIZE];

private:
	int bitmapId1;
	int bitmapId2;
	int bitmapId3;
	int bitmapId4;

	int black;
	int white;

private:
	void DataProcessing(Packet);
};
#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#define _WINSOCKAPI_ 
#pragma once

#include <iostream>
#include <string.h>

#define MAX_PACKET_SIZE 1000000
#define MAX_MESSAGE_SIZE 1024

enum PacketTypes {

	INIT_CONNECTION = 0,

	ACTION_EVENT = 1,

};

struct Packet {

	unsigned int packet_type;
	unsigned int client_id;

	char message[MAX_MESSAGE_SIZE];

	Packet(){}

	~Packet(){}

	void serialize(char * data) 
	{
		memcpy(data, this, sizeof(Packet));
	}

	void deserialize(char * data) 
	{
		memcpy(this, data, sizeof(Packet));
	}
};

#endif
#pragma once

#include <iostream>
#include <string.h>

#define MAX_PACKET_SIZE 1000000
#define MAX_MESSAGE_SIZE 1024

enum PacketTypes {

	INIT_CONNECTION = 0,
	START_EVENT= 1,
	MESSAGE_EVENT = 2,
	GAME_EVENT = 3,
	EMPTY_PACKET = 4
};

struct Packet {

	unsigned int packet_type;

	unsigned int client_id;

	bool startGame;

	int level;

	char message[MAX_MESSAGE_SIZE];

	int bitmapId1;
	int bitmapId2;
	int bitmapId3;
	int bitmapId4;

	int black;
	int white;

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
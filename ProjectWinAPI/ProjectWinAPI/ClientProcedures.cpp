#include "ClientProcedures.h"

ClientProcedures::ClientProcedures(void)
{
	network = new ClientNetwork();
	sendInitPacket();
}

ClientProcedures::~ClientProcedures(void)
{
}

void ClientProcedures::sendInitPacket()
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientProcedures::sendMessagePacket(char msg[])
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];
	
	Packet packet;
	packet.packet_type = MESSAGE_EVENT;
	packet.client_id = Form1::clientId;

	int i = 0;
	for (i; i < MAX_MESSAGE_SIZE; i++)
	{
		packet.message[i] = msg[i];
	}

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

void ClientProcedures::sendGamePacket(int id1, int id2, int id3, int id4)
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = GAME_EVENT;
	packet.client_id = Form1::clientId;

	packet.bitmapId1 = id1;
	packet.bitmapId2 = id2;
	packet.bitmapId3 = id3;
	packet.bitmapId4 = id4;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

Packet ClientProcedures::update()
{
	Packet packet;
	int data_length = network->receivePackets(network_data);
	
	if (data_length <= 0)
	{
		packet.packet_type = EMPTY_PACKET;
		return packet;
	}

	int i = 0;
	while (i < (unsigned int)data_length)
	{
		packet.deserialize(&(network_data[i]));
		i += sizeof(Packet);

		return packet;
	}
}


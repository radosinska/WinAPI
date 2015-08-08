#include "ClientProcedures.h"

ClientProcedures::ClientProcedures(void)
{

	network = new ClientNetwork();

	// send init packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}


ClientProcedures::~ClientProcedures(void)
{
}

void ClientProcedures::sendActionPackets(char msg[])
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];
	
	Packet packet;
	packet.packet_type = ACTION_EVENT;

	int i = 0;
	for (i; i < MAX_MESSAGE_SIZE; i++)
	{
		packet.message[i] = msg[i];
	}

	packet.serialize(packet_data);

	NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
}

char* ClientProcedures::update()
{
	Packet packet;
	int data_length = network->receivePackets(network_data);

	int messageLength;
	char *msg;
	int k;

	if (data_length <= 0)
	{
		//no data recieved
		return NULL;
	}

	int i = 0;
	while (i < (unsigned int)data_length)
	{
		packet.deserialize(&(network_data[i]));
		i += sizeof(Packet);

		switch (packet.packet_type) {

		case ACTION_EVENT:

			//printf("client received action event packet from server\n");

			messageLength = strlen(packet.message);
			msg = (char *)malloc(1 + messageLength);

			k = 0;
			for (k; k < messageLength; k++)
			{
				msg[k] = packet.message[k];
			}
			msg[k] = '\0';
			return msg;

		default:

			//printf("error in packet types\n");

			return NULL;
		}
	}
}


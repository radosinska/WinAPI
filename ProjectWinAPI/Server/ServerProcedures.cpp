#include "ServerProcedures.h"

unsigned int ServerProcedures::client_id;

ServerProcedures::ServerProcedures(void)
{
	client_id = 0;
	network = new ServerNetwork();
}

ServerProcedures::~ServerProcedures(void)
{
}

void ServerProcedures::update()
{
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);
		sendInitPacket();

		if (client_id % 2 == 1)
		{
			this->sendStartGamePackets();
		}

		//TODO: only to test here
		if (client_id == 0)
		{
			srand(time(NULL));
			this->bitmapId1 = (std::rand() % 7) + 112;
			this->bitmapId2 = (std::rand() % 7) + 112;
			this->bitmapId3 = (std::rand() % 7) + 112;
			this->bitmapId4 = (std::rand() % 7) + 112;
		}

		client_id++;
	}

	receiveFromClients();
}

void ServerProcedures::receiveFromClients()
{

	Packet packet;

	std::map<unsigned int, SOCKET>::iterator iter;

	for (iter = network->sessions.begin(); iter != network->sessions.end(); iter++)
	{
		int data_length = network->receiveData(iter->first, network_data);

		if (data_length <= 0)
		{
			//no data recieved
			continue;
		}

		int i = 0;
		while (i < (unsigned int)data_length)
		{
			packet.deserialize(&(network_data[i]));
			i += sizeof(Packet);

			switch (packet.packet_type) {

			case INIT_CONNECTION:
				//sendInitPacket();
				break;

			case MESSAGE_EVENT:
				printf("server received message event packet from client: ");
				std::cout << packet.message;
				printf("\n");
				
				sendMessagePackets(packet.message,packet.client_id);
				break;

			case GAME_EVENT:
				DataProcessing(packet);
				break;

			default:
				printf("error in packet types\n");
				break;
			}
		}
	}
}

void ServerProcedures::sendInitPacket()
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;
	packet.client_id = client_id;

	packet.serialize(packet_data);

	network->sendToUser(client_id, packet_data, packet_size);
}

void ServerProcedures::sendStartGamePackets()
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = START_EVENT;
	packet.client_id = client_id-1;

	packet.serialize(packet_data);

	network->sendToUser(client_id - 1, packet_data, packet_size);
	Sleep(1000);
	network->sendToUser(client_id, packet_data, packet_size);
}

void ServerProcedures::sendMessagePackets(char msg[], int clientId)
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = MESSAGE_EVENT;
	packet.client_id = clientId;
	
	int i = 0;
	for (i; i < MAX_MESSAGE_SIZE; i++)
	{
		packet.message[i] = msg[i];
	}

	packet.serialize(packet_data);

	network->sendToUser(clientId, packet_data, packet_size);
	if (clientId % 2 == 1)
	{
		network->sendToUser(clientId - 1, packet_data, packet_size);
	}
	else
	{
		network->sendToUser(clientId + 1, packet_data, packet_size);
	}
}

void ServerProcedures::sendGamePackets(int clientId, int bitmap1, int bitmap2, int bitmap3, int bitmap4)
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = GAME_EVENT;
	packet.client_id = clientId;
	
	packet.black = this->black;
	packet.white = this->white;
	packet.bitmapId1 = bitmap1;
	packet.bitmapId2 = bitmap2;
	packet.bitmapId3 = bitmap3;
	packet.bitmapId4 = bitmap4;

	packet.serialize(packet_data);

	network->sendToUser(clientId, packet_data, packet_size);
	if (clientId % 2 == 1)
	{
		network->sendToUser(clientId - 1, packet_data, packet_size);
	}
	else
	{
		network->sendToUser(clientId + 1, packet_data, packet_size);
	}
}

void ServerProcedures::DataProcessing(Packet packet)
{
	this->black = 0;
	this->white = 0;

	int serverCombination[4] = { bitmapId1, bitmapId2, bitmapId3, bitmapId4 };
	int userCombination[4] = { packet.bitmapId1, packet.bitmapId2, packet.bitmapId3, packet.bitmapId4 };

	for (int i = 0; i < 4; i++)
	{
		if (serverCombination[i] == userCombination[i])
		{
			black++;
			serverCombination[i] = 0;
			userCombination[i] = 0;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (userCombination[i] != 0)
		{
			for (int j = 0; j < 4; j++)
			{
				if (userCombination[i] == serverCombination[j])
				{
					white++;
					serverCombination[j] = 0;
					userCombination[i] = 0;
					break;
				}
			}
		}
		if (black + white == 4)
		{
			break;
		}
	}

	this->sendGamePackets(packet.client_id,packet.bitmapId1, packet.bitmapId2, packet.bitmapId3, packet.bitmapId4);
}
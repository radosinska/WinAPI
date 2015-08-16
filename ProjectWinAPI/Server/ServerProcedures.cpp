#include "ServerProcedures.h"

unsigned int ServerProcedures::client_id;

ServerProcedures::ServerProcedures(void)
{
	// id's to assign clients for our table
	client_id = 0;

	// set up the server network to listen 
	network = new ServerNetwork();
}

ServerProcedures::~ServerProcedures(void)
{
}

void ServerProcedures::update()
{
	// get new clients
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id);

		if (client_id % 2 == 1)
		{
			this->sendStartGamePackets();
		}

		//TODO: only to test here
		if (client_id == 0)
		{
			srand(time(NULL));
			//int wylosowana_liczba =( std::rand() % ile_liczb_w_przedziale ) + startowa_liczba;
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

	// go through all clients
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

				//server received init packet from client
				//sendActionPackets();
				break;

			case MESSAGE_EVENT:

				printf("server received message event packet from client: ");
				std::cout << packet.message;
				printf("\n");
				
				//Przes³anie tej wiadomoœci do wszystkich klientów
				sendMessagePackets(packet.message);

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

void ServerProcedures::sendStartGamePackets()
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = START_EVENT;
	packet.client_id = client_id;

	packet.serialize(packet_data);

	network->sendToUser(client_id - 1, packet_data, packet_size);
	network->sendToUser(client_id, packet_data, packet_size);
}

void ServerProcedures::sendMessagePackets(char msg[])
{
	// send action packet
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = MESSAGE_EVENT;
	packet.client_id = client_id;
	
	int i = 0;
	for (i; i < MAX_MESSAGE_SIZE; i++)
	{
		packet.message[i] = msg[i];
	}

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}

void ServerProcedures::sendGamePackets(int, int)
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = GAME_EVENT;
	packet.client_id = client_id;
	
	packet.black = this->black;
	packet.white = this->white;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}

void ServerProcedures::DataProcessing(Packet packet)
{
	this->black = 0;
	this->white = 0;

	int serverCombination[4] = { bitmapId1, bitmapId2, bitmapId3, bitmapId4 };
	int userCombination[4] = { packet.bitmapId1, packet.bitmapId2, packet.bitmapId3, packet.bitmapId4 };

	//TODO: process data
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

	//TODO: send reply
	this->sendGamePackets(black, white);
}
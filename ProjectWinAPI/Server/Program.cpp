#include "ServerProcedures.h"

// used for multi-threading
#include <process.h>

void serverLoop();

ServerProcedures * server;


int main()
{
	// initialize the server
	server = new ServerProcedures();
	
	printf("Server is running.\n");
	serverLoop();

	system("pause");
}

void serverLoop()
{
	while (true)
	{
		server->update();
	}
}
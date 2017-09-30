#include<stdio.h>
#include<winsock2.h>
#include <random>
#include <time.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define printf(x) logging_enabled?printf(x):0;

namespace MyNet
{
	bool logging_enabled = true;

	void disable_logging()
	{
		logging_enabled = false;
	}

	void enable_logging()
	{
		logging_enabled = true;
	}

	int init() //Initialize Winsock
	{
		srand(time(0));
		WSADATA wsa;
		printf("\nInitialising Winsock...%d", rand());
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			printf("Failed. Error Code : %d\n", WSAGetLastError());
			return -1;
		}
		printf("Initialised.\n");
		return 0;
	}

	/*
	int host()
	{
		if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		{
			printf("Could not create socket : %d", WSAGetLastError());
		}
		printf("Socket created.\n");

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(PORT);

		//Bind
		if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
		{
			printf("Bind failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
	*/

	void terminate()
	{
		WSACleanup();
	}
}
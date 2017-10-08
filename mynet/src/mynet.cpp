#include <stdio.h>
#include <winsock2.h>
#include <vector>
#include "Ws2tcpip.h"
#include "mynet.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library


namespace MyNet
{
	SOCKET sockhandler::serv_sock = INVALID_SOCKET;
	SOCKET sockhandler::client_sock = INVALID_SOCKET;
	bool sockhandler::is_serv = false;

	bool logging_enabled = true;

	int sockhandler::setup_sockets()
	{
		serv_sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (serv_sock == INVALID_SOCKET)
		{
			logging_enabled ? printf("Could not create server socket : %d\n", WSAGetLastError()) : 0;
			return -1;
		}
		logging_enabled ? printf("Server socket created.\n") : 0;

		client_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (serv_sock == INVALID_SOCKET)
		{
			logging_enabled ? printf("Could not create client socket : %d\n", WSAGetLastError()) : 0;
			return -1;
		}
		logging_enabled ? printf("Client socket created.\n") : 0;
		return 0;
	}

	int sockhandler::close_sockets()
	{
		if (closesocket(serv_sock) == SOCKET_ERROR)
		{
			logging_enabled ? printf("closesocket() failed with error code : %d", WSAGetLastError()) : 0;
			return -1;
		}

		if (closesocket(client_sock) == SOCKET_ERROR)
		{
			logging_enabled ? printf("closesocket() failed with error code : %d", WSAGetLastError()) : 0;
			return -1;
		}
		
		return 0;
	}

	SOCKET* sockhandler::get_serv_sock()
	{
		return &serv_sock;
	}

	SOCKET* sockhandler::get_client_sock()
	{
		return &client_sock;
	}

	bool sockhandler::is_server()
	{
		return is_serv;
	}

	std::string Address::to_str()
	{
		char buf[16];
		InetNtop(addr.sin_family, &(addr.sin_addr), buf, 16);
		return std::string(buf) + std::string(":") + std::to_string(ntohs(addr.sin_port));
	}

	Address::Address() :
		len(sizeof(addr))
	{
		memset((char *)&addr, 0, len);
	}

	Address::Address(std::string ip, unsigned short port) :
		len(sizeof(addr))
	{
		memset((char *)&addr, 0, len);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		InetPton(AF_INET, ip.c_str(), &addr.sin_addr.S_un.S_addr);
	}

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
		WSADATA wsa;
		logging_enabled ? printf("\nInitialising Winsock...\n") : 0;
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			logging_enabled ? printf("Failed. Error Code : %d\n", WSAGetLastError()) : 0;
			return -1;
		}

		sockhandler::setup_sockets();

		logging_enabled ? printf("...initialised.\n") : 0;
		return 0;
	}
	
	int host(unsigned short port)
	{
		sockhandler::is_serv = true;

		struct sockaddr_in server;

		//Prepare the sockaddr_in structure
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(port);

		//Bind
		if (bind(*sockhandler::get_serv_sock(), (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
		{
			logging_enabled ? printf("Bind failed with error code : %d", WSAGetLastError()) : 0;
			return -1;
		}
		return 0;
	}

	int recieve(char* buffer, int size, Address* a)
	{
		if (recvfrom(sockhandler::is_server() ? *sockhandler::get_serv_sock() : *sockhandler::get_client_sock(),
					 buffer, size, NULL, (sockaddr*)&(a->addr), &(a->len)) == SOCKET_ERROR)
		{
			logging_enabled ? printf("recvfrom() failed with error code : %d", WSAGetLastError()) : 0;
			return -1;
		}
		return 0;
	}
	
	int send(char* msg, int length, Address* to)
	{
		if (sendto(sockhandler::is_server() ? *sockhandler::get_serv_sock() : *sockhandler::get_client_sock(),
				   msg, length, 0, (sockaddr*) &(to->addr), to->len) == SOCKET_ERROR)
		{
			logging_enabled ? printf("sendto() failed with error code : %d", WSAGetLastError()) : 0;
			return -1;
		}
		return 0;
	}

	void terminate()
	{
		sockhandler::close_sockets();
		WSACleanup();
	}
};

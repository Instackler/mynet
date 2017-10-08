#pragma once
#include "Ws2tcpip.h"
#include <string>


namespace MyNet
{
	class sockhandler
	{
		static bool is_serv;
		static SOCKET serv_sock;
		static SOCKET client_sock;
	public:
		sockhandler() = delete;
		sockhandler(const sockhandler&) = delete;
		sockhandler& operator=(const sockhandler&) = delete;
		static int setup_sockets();
		static int close_sockets();
		static SOCKET* get_serv_sock();
		static SOCKET* get_client_sock();
		static bool is_server();
		friend int host(unsigned short port);
	};

	class Address
	{
	private:
		sockaddr_in addr;
		int len;
	public:
		std::string to_str(); // Returns human-readable string representation of an Address
		Address();
		Address(std::string ip, unsigned short port);
		bool operator==(const Address&) const;
		bool operator!=(const Address&) const;
		friend int recieve(char* buffer, int size, Address* addr); // Recieve a datagram from address addr
		friend int recieve_peek(char* buffer, int size, Address* addr); //Get address of the sender
		friend int send(char* msg, int length, Address* to); // Send datagram to address to
	};
	
	void disable_logging();
	void enable_logging();
	void terminate(); //Clean up
	int init(); // Initialize WinSock
}

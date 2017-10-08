#pragma comment(lib,"mynet.lib")
#include <iostream>
#include <string>
#include "mynet.h"
#include <glfw3.h>
#include <thread>
#include <vector>

using namespace MyNet;
using namespace std;
char m[] = "HelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHello";
Address ad(std::string("127.0.0.1"), (unsigned short)65565);
const int num_threads = 2;


void client()
{
	send(m, 1001, &ad);
	for (int i = 0; i < 256; ++i)
	{
		recieve(m, 1001, &ad);
		send(m, 1001, &ad);
	}
	cout << m << endl;
}

int main()
{
	//MyNet::disable_logging();
	init();
	vector<thread*> threads;

	std::cin.get();
	for (int i = 0; i < num_threads; ++i)
	{
		threads.push_back(new thread(client));
		cout << "New thread spawned" << endl;
	}

	
	for (int i = 0; i < num_threads; ++i)
	{
		threads[i]->join();
		cout << "A thread has joined" << endl;
	}
	for (int i = 0; i < num_threads; ++i)
	{
		delete threads[i];
	}

	cin.get();
	MyNet::terminate();
	return 0;
}
#include "mynet.h"
#pragma comment(lib,"mynet.lib")
#include <iostream>
#include <glfw3.h>
#include <thread>

using namespace MyNet;
using namespace std;


int main()
{
	glfwInit();
	MyNet::init();
	MyNet::host((unsigned short)65565);
	Address a;
	char message[1001];
	double time;

	recieve(message, 1001, &a);
	time = glfwGetTime();
	for (int i = 0; i < 256; ++i)
	{
		send(message, 1001, &a);
		recieve(message, 1001, &a);
	}
	time = glfwGetTime() - time;
	cout << time << endl;

	cin.get();
	MyNet::terminate();
	return 0;
}
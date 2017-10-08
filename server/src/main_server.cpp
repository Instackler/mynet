#include "mynet.h"
#pragma comment(lib,"mynet.lib")
#include <iostream>
#include <glfw3.h>
#include <thread>
#include <vector>

using namespace MyNet;
using namespace std;
const unsigned short MAX_CLIENTS = 3;
double t;
char message[1001];
vector<Address*> a;
int num = 0;


void process(Address* addr)
{
	t = glfwGetTime();
	for (int i = 0; i < 256; ++i)
	{
		send(message, 1001, addr);
		recieve(message, 1001, addr);
	}
	t = glfwGetTime() - t;
	cout << "Thread " << num++ << " finished in " << t << " seconds" << endl;
	delete addr;
}

bool check_if_exists(const Address* const _a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		if (*_a == *a[i])
		{
			return true;
		}
	}
	return false;
}

int main()
{
	glfwInit();
	MyNet::init();
	MyNet::host((unsigned short)65565);

	for (;;)
	{
		Address* pa = new Address();
		recieve_peek(message, 1001, pa);
		if (!check_if_exists(pa))
		{
			a.push_back(pa);
			thread thr(process, pa);
			thr.detach();
		}
		else
		{
			delete pa;
		}
		Sleep(5);
	}


	cin.get();
	MyNet::terminate();
	return 0;
}
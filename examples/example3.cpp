#include "../src/log.h"
#include <thread>

void threadFunc(int ind)
{
	for (int i = 0; i < 100000; ++i)
	{
		LOG << "thread" << ind << " : " << i;
	}
}

int main(){

	thread tmp1(threadFunc, 1);
	thread tmp2(threadFunc, 2);
	thread tmp3(threadFunc, 3);
	thread tmp4(threadFunc, 4);
	tmp1.join();
	tmp2.join();
	tmp3.join();
	tmp4.join();

}

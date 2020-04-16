#include <thread>
#include <iostream>
#include <string.h>
#include "log.h"

using namespace std;

void threadFunc(int ind)
{
	for (int i = 0; i < 100000; ++i)
	{
		LOG <<"thread"<<ind<<" : "<<i;
	}
}

void type_test()
{
	// 13 lines
	cout << "----------type test-----------" << endl;
	LOG << 0;
	LOG << 1234567890123;
	LOG << 1.0f;
	LOG << 3.1415926;
	LOG << (short)1;
	LOG << (long long)1;
	LOG << (unsigned int)1;
	LOG << (unsigned long)1;
	LOG << (long double) 1.6555556;
	LOG << (unsigned long long) 1;
	LOG << 'c';
	LOG << "abcdefg";
	LOG << string("This is a string");
}

void stressing_single_thread()
{
	// 100000 lines
	cout << "----------stressing test single thread-----------" << endl;
	for (int i = 0; i < 100000; ++i)
	{
		LOG << i;
	}
}

void stressing_multi_threads(int threadNum = 4)
{
	// threadNum * 100000 lines
	cout << "----------stressing test multi thread-----------" << endl;
	
	
	thread tmp1(threadFunc,1);
	thread tmp2(threadFunc, 2);
	thread tmp3(threadFunc, 3);
	thread tmp4(threadFunc, 4);
	tmp1.join();
	tmp2.join();
	tmp3.join();
	tmp4.join();
}

void other()
{
	// 1 line
	cout << "----------other test-----------" << endl;
	LOG << "fddsa" << 'c' << 0 << 3.666 << string("This is a string");
}

int main(){

	type_test();

	stressing_single_thread();

	stressing_multi_threads();

	other();

	return 0;

}

#include "../src/log.h"

int main(){

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

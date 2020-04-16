# sddlog

a simple log for Linux and Windows
(learn from muduo)

# features

  采用双缓冲技术，将前后端分离
  
  仅当写入一定次数或达到一定时长，才进行文件的写入，减少额外的系统开销
  
  格式化输出信息

  单线程写入100w条日志需1-2秒，4线程每条线程写入100w条日志需12-13秒（每条日志70字节左右）
  
# use


```
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
  LOG << "fddsa" << 'c' << 0 << 3.666 << string("This is a string");

}
```

```
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
```

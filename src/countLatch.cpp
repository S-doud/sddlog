#include "countLatch.h"

sdd::CountLatch::CountLatch(int count)
	:count_(count),
	mutex_(),
	cv_()
{
}

sdd::CountLatch::~CountLatch()
{
}

void sdd::CountLatch::wait()
{
	std::unique_lock<std::mutex> lck(mutex_);
	while (count_)
	{
		cv_.wait(lck);
	}
}

void sdd::CountLatch::countDown()
{
	std::unique_lock<std::mutex> lck(mutex_);
	--count_;
	if (count_ == 0) {
		cv_.notify_all();
	}
}

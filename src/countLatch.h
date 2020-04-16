#pragma once
#include <mutex>
#include <condition_variable>

namespace sdd {
	class CountLatch
	{
	private:
		std::mutex mutex_;
		std::condition_variable cv_;
		int count_;

	public:
		CountLatch(int count);
		~CountLatch();

		void wait();
		void countDown();
	};
}



#pragma once
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <string>
#include <vector>
#include <chrono>
#include "countLatch.h"
#include "logfile.h"
#include "otherbuffers.h"
#include "logthread.h"

namespace sdd {
	class Logging
	{
	private:
		using Buffer = Buffers<largesize>;
		using BufferPtr = std::shared_ptr<Buffer>;
		using BufferVector = std::vector<BufferPtr>;
		CountLatch latch_;
		LogThread thread_;
		std::mutex mutex_;
		std::condition_variable cond_;
		BufferPtr firstBuffer_;
		BufferPtr secondBuffer_;
		BufferVector buffers_;
		std::string fileName_;
		bool isrunning_;
	public:
		Logging(std::string fileName);
		~Logging();

		void append(const char *logptr, size_t len);
		void start();
		void stop();

	private:
		void threadFun();


	};

}


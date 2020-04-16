#include "logging.h"

namespace sdd {
	Logging::Logging(std::string fileName)
		:isrunning_(false),
		fileName_(fileName),
		latch_(1),
		thread_(std::bind(&Logging::threadFun,this)),
		mutex_(),
		cond_(),
		firstBuffer_(new Buffer),
		secondBuffer_(new Buffer),
		buffers_()
	{
		firstBuffer_->init();
		secondBuffer_->init();
		buffers_.reserve(16);
	}

	Logging::~Logging()
	{
		if (isrunning_)
		{
			stop();
		}
	}

	void Logging::append(const char * logptr, size_t len)
	{
		std::lock_guard<std::mutex> lck(mutex_);
		if (firstBuffer_->avail() > len) {
			firstBuffer_->append(logptr, len);
		}
		else
		{
			buffers_.push_back(std::move(firstBuffer_));
			firstBuffer_.reset();
			if (secondBuffer_) {
				firstBuffer_=std::move(secondBuffer_);
			}
			else 
			{
				firstBuffer_.reset(new Buffer);
			}
			firstBuffer_->append(logptr, len);
			cond_.notify_one();
		}
	}

	void Logging::start()
	{
		isrunning_ = true;
		thread_.start();
		latch_.wait();
	}

	void Logging::stop()
	{
		isrunning_ = false;
		thread_.join();
	}

	void Logging::threadFun()
	{
		
		LogFile output(fileName_);
		BufferVector writebuffers;
		writebuffers.reserve(16);
		BufferPtr newBuffer1(new Buffer);
		BufferPtr newBuffer2(new Buffer);
		newBuffer1->init();
		newBuffer2->init();
		latch_.countDown();
		while (isrunning_)
		{
			{
				std::unique_lock<std::mutex> lck(mutex_);
				if (buffers_.empty())  
				{
					cond_.wait_for(lck, std::chrono::seconds(2));
				}
				buffers_.push_back(std::move(firstBuffer_));
				firstBuffer_.reset();

				firstBuffer_ = std::move(newBuffer1);
				writebuffers.swap(buffers_);
				if (!secondBuffer_) {
					secondBuffer_ = std::move(newBuffer2);
				}
			}

			for (size_t i = 0; i < writebuffers.size(); ++i) {
				output.append(writebuffers[i]->data(), writebuffers[i]->length());
			}

			if (writebuffers.size() > 2) {
				writebuffers.resize(2);
			}

			if (!newBuffer1) {
				newBuffer1 = writebuffers.back();
				writebuffers.pop_back();
				newBuffer1->reset();
			}

			if (!newBuffer2) {
				newBuffer2 = writebuffers.back();
				writebuffers.pop_back();
				newBuffer2->reset();
			}

			writebuffers.clear();
			output.flush();
		}
		output.flush();
	}
}

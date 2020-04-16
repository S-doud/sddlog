#include "logthread.h"

namespace sdd{
    LogThread::LogThread(std::function<void()> fun)
    :started_(false),
    joined_(false),
    threadname_("LogThread"),
    threadfunc_(fun),
    threadptr_(nullptr){

    }

    LogThread::~LogThread(){
        this->join();
		delete threadptr_;
    }

    bool LogThread::isstart() const{
        return started_;
    }

    void LogThread::start(){
		if (started_ == false) {
			threadptr_ = new std::thread(threadfunc_);
			started_ = true;
		}
    }

    void LogThread::join(){
		if (joined_ == false) {
			threadptr_->join();
			joined_ = true;
		}
    }

    std::string LogThread::getname() const{
        return threadname_;
    }
}
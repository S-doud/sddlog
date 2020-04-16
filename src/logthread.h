#pragma once
#include <thread>
#include <functional>
#include <string>

namespace sdd{
    class LogThread
    {
    private:
        std::function<void()> threadfunc_ ;
        bool started_;
        bool joined_;
        std::string threadname_;
        std::thread *threadptr_;

    public:
        explicit LogThread(std::function<void()> fun);
        ~LogThread();

        void start();
        void join();
        bool isstart() const;
        std::string getname() const;
        

    };
}




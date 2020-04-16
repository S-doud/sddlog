#pragma once
#include <stdio.h>
#include <string>
#include <mutex>
#include <memory>

namespace sdd{
    class LogFile
    {
    private:
        FILE* fl_;
        char buffer_[64*1024];
        int count;
        int perN;
        std::unique_ptr<std::mutex> mtx;

    public:
        explicit LogFile(std::string filename);
        ~LogFile();

        void append(const char* logptr,size_t len);
        void flush();

    private:
        void write(const char* logptr,size_t len);
        
    };
}



#include "logfile.h"

namespace sdd{
    LogFile::LogFile(std::string filename)
    :fl_(fopen(filename.c_str(),"a")),
    count(0),
    perN(1024),
    mtx(new std::mutex())
    {
        setbuf(fl_,buffer_);
    }

    LogFile::~LogFile(){
        fclose(fl_);
    }

    void LogFile::append(const char* logptr,size_t len){
        std::lock_guard<std::mutex> lock(*mtx);
        write(logptr,len);
        ++count;
        if(count>=perN){
            this->flush();
            count=0;
        }
    }

    void LogFile::flush(){
        fflush(fl_);
    }

    void LogFile::write(const char* logptr,size_t len){
        size_t n=fwrite(logptr,len,1,fl_);
        if(n!=0&&n!=1){
            std::abort();
        }
    }

}
#include "log.h"
#include <iostream>

static std::string logFileName = "./log.txt";
static sdd::Logging *logging_=new sdd::Logging(logFileName);


namespace sdd {
	std::once_flag flag1;

	void once_init()
	{
		logging_->start();
	}

	void output(const char* msg, int len)
	{
		std::call_once(flag1, once_init);
		logging_->append(msg, len);
	}

	Log::Log(std::string fileName,int line)
		:fileName_(fileName),
		stream_()
	{
		getTime();
	}

	Log::~Log()
	{
		const Buffers<smallsize>& buf(stream().buffer());
		output(buf.data(), buf.length());
		output("\n", 1);
	}

	LogStream & Log::stream()
	{
		return stream_;
	}

	void Log::getTime()
	{
		char tbuf_[64] = { 0 };
		time_t rawtime;
		struct tm *ptminfo;
		time(&rawtime);
		ptminfo = localtime(&rawtime);
		snprintf(tbuf_ , sizeof(tbuf_),"%4d-%02d-%02d %02d:%02d:%02d\n" ,
			ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
			ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);
		stream_ << tbuf_;
	}
}
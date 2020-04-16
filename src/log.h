#pragma once
#include "logstream.h"
#include "logging.h"
#include <string>

namespace sdd {
	class Log
	{
	private:
		std::string fileName_;
		int line_;
		LogStream stream_;
		

	public:
		Log(std::string fileName,int line);
		~Log();
		LogStream& stream();
	private:
		void getTime();
	};
}

#define LOG sdd::Log(__FILE__,__LINE__).stream()



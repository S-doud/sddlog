#pragma once
#include "otherbuffers.h"

namespace sdd {
	class LogStream
	{
	private:
		const int stdintsize = 32;
		Buffers<smallsize> buffer_;

	public:
		LogStream();
		~LogStream();
		
		void append(const char * logptr, size_t len);
		void resetBuffer();
		const Buffers<smallsize>& buffer() const;

		LogStream& operator<<(bool val);
		LogStream& operator<<(short val);
		LogStream& operator<<(unsigned short val);
		LogStream& operator<<(int val);
		LogStream& operator<<(unsigned int val);
		LogStream& operator<<(long val);
		LogStream& operator<<(unsigned long val);
		LogStream& operator<<(long long val);
		LogStream& operator<<(unsigned long long val);
		LogStream& operator<<(float val);
		LogStream& operator<<(double val);
		LogStream& operator<<(long double val);
		LogStream& operator<<(char val);
		LogStream& operator<<(const char* str);
		LogStream& operator<<(const unsigned char* str);
		LogStream& operator<<(const std::string& str);


	private:
		template<typename T>
		void stdint(T t);

	};
}


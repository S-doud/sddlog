#include "logstream.h"
#include <algorithm>

const char digits[] = "9876543210123456789";
const char* zero = digits + 9;

// From muduo
template <typename T>
size_t convert(char buf[], T value) {
	T i = value;
	char* p = buf;

	do {
		int lsd = static_cast<int>(i % 10);
		i /= 10;
		*p++ = zero[lsd];
	} while (i != 0);

	if (value < 0) {
		*p++ = '-';
	}
	*p = '\0';
	std::reverse(buf, p);

	return p - buf;
}


namespace sdd {
	LogStream::LogStream() {};
	LogStream::~LogStream() {};


	void LogStream::append(const char *logptr, size_t len) {
		buffer_.append(logptr, len);
	}

	void LogStream::resetBuffer() { buffer_.reset(); }

	const Buffers<smallsize>& LogStream::buffer() const { return buffer_; }

	template<typename T>
	void LogStream::stdint(T t) {
		if (buffer_.avail() > stdintsize) {
			size_t len = convert(buffer_.current(), t);
			buffer_.add(len);
		}
	}


	LogStream & LogStream::operator<<(bool val)
	{
		buffer_.append(val ? "1" : "0", 1);
		return *this;
	}

	LogStream & LogStream::operator<<(short val)
	{
		*this << static_cast<int>(val);
		return *this;
	}

	LogStream & LogStream::operator<<(unsigned short val)
	{
		*this << static_cast<unsigned int>(val);
		return *this;
	}

	LogStream & LogStream::operator<<(int val)
	{
		stdint(val);
		return *this;
	}

	LogStream & LogStream::operator<<(unsigned int val)
	{
		stdint(val);
		return *this;
	}

	LogStream & LogStream::operator<<(long val)
	{
		stdint(val);
		return *this;
	}

	LogStream & LogStream::operator<<(unsigned long val)
	{
		stdint(val);
		return *this;
	}

	LogStream & LogStream::operator<<(long long val)
	{
		stdint(val);
		return *this;
	}

	LogStream & LogStream::operator<<(unsigned long long val)
	{
		stdint(val);
		return *this;
	}

	LogStream & LogStream::operator<<(float val)
	{
		*this << static_cast<double>(val);
		return *this;
	}

	LogStream & LogStream::operator<<(double val)
	{
		if (buffer_.avail() >= stdintsize) {
			int len = snprintf(buffer_.current(), stdintsize, "%.12g", val);
			buffer_.add(len);
		}
		return *this;
	}

	LogStream & LogStream::operator<<(long double val)
	{
		if (buffer_.avail() >= stdintsize) {
			int len = snprintf(buffer_.current(), stdintsize, "%.12Lg", val);
			buffer_.add(len);
		}
		return *this;
	}

	LogStream & LogStream::operator<<(char val)
	{
		buffer_.append(&val, 1);
		return *this;
	}

	LogStream & LogStream::operator<<(const char * str)
	{
		if (str)
			buffer_.append(str, strlen(str));
		else
			buffer_.append("(null)", 6);
		return *this;
	}

	LogStream & LogStream::operator<<(const unsigned char * str)
	{
		*this<<(reinterpret_cast<const char*>(str));
		return *this;
	}

	LogStream & LogStream::operator<<(const std::string & str)
	{
		buffer_.append(str.c_str(), str.size());
		return *this;
	}

	
	

}

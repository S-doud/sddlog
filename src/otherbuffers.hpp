#pragma once
#include <string>
const int smallsize= 4000;
const int largesize= 4000*64;
namespace sdd {
	
	template<int SIZE>
	class Buffers
	{
	public:
		Buffers():cur_(data_){}
		~Buffers(){}

		void append(const char *logptr,size_t len) {
			if (avail() > static_cast<int>(len)) {
				memcpy(cur_, logptr, len);
				cur_ += len;
			}
		}

		const char *data() const { return data_; }
		const char *end() const { return data_ + sizeof(data_); }
		char *current() const { return cur_; }


		size_t length() const { return static_cast<size_t>(cur_ - data_); }
		int avail() const { return static_cast<int>(end() - cur_); }
		void reset() { cur_ = data_; }
		void add(size_t len) { cur_ += len; }
		void init() { memset(data_,0,sizeof(data_)); }
		
	private:
		char *cur_;
		char data_[SIZE];

	};

}

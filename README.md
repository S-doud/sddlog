# sddlog
a simple log library for Linux and Windows
(learn from muduo)

# features
  采用双缓冲技术，降低线程的额外开销
  仅当写入一定次数或达到一定时长，才进行文件的写入，减少额外的系统开销
  格式化输出信息

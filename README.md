# sddlog

a simple log for Linux and Windows
(learn from muduo)

# features

  采用双缓冲技术，将前后端分离
  
  仅当写入一定次数或达到一定时长，才进行文件的写入，减少额外的系统开销
  
  格式化输出信息

  单线程写入100w条日志需1-2秒，4线程每条线程写入100w条日志需12-13秒（每条日志70字节左右）
  
# how to use

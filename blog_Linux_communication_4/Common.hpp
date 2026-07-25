#ifndef __COMMON_NAMEDPIPE_
#define __COMMON_NAMEDPIPE_

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <cstdlib>
#include <string>
#include <fcntl.h>
#include <cstring>
#define PIPE_FILE "./fifo"

#define ERR_EXIT(m)         \
    do                      \
    {                       \
        perror(m);          \
        exit(EXIT_FAILURE); \
                            \
    } while (false)

class NamedPipe
{
public:
    void Create(std ::string file = PIPE_FILE)
    {
        umask(0);
        int n = mkfifo(file.c_str(), 0666);
        if (n == -1)
            ERR_EXIT("mkfifo");
    }
    void Destory(std ::string file = PIPE_FILE)
    {
        int n = unlink(file.c_str());
        if (n == -1)
            ERR_EXIT("unlink");
    }
    void OpenForRead(std ::string file = PIPE_FILE)
    {
        _pipefd = open(file.c_str(), O_RDONLY);
        if (_pipefd == -1)
            ERR_EXIT("open_read");
    }
    void OpenForWrite(std ::string file = PIPE_FILE)
    {
        _pipefd = open(file.c_str(), O_WRONLY);
        if (_pipefd == -1)
            ERR_EXIT("open_write");
    }
    void Read(int outfd)
    {
        //读取管道内容到外部文件中
        char _buffer[1024];
        while(read(_pipefd, _buffer, sizeof(_buffer)) != 0)
        {
            int n = write(outfd , _buffer , sizeof(_buffer));
            if(n < 0 )
                ERR_EXIT("write") ;
            memset(_buffer , 0 , sizeof(_buffer));
        }
    }
    void Write(int infd)
    {
        char _buffer[1024];
        //将文件中的内容读取到缓冲区buffer
        while (read(infd, _buffer, sizeof(_buffer)) != 0)
        {
            int n = write(_pipefd, _buffer, sizeof(_buffer));
            if (n < 0)
                ERR_EXIT("write");
            memset(_buffer , 0 , sizeof(_buffer));
        }
    }

private:
    int _pipefd;
};

#endif
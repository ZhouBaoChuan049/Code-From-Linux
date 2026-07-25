#include "Common.hpp"
int main()
{
    //读取管道内容到缓冲区
    NamedPipe pipe ;
    pipe.OpenForRead(PIPE_FILE);
    int outfd = open("destnation.txt",O_WRONLY);
    if(outfd == -1) 
        ERR_EXIT("open");
    pipe.Read(outfd) ;
    //缓冲区内容写入一个Object.txt文件。
    return 0 ;
}
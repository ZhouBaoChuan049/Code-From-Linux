#include "Common.hpp"
int main()
{
    //从文件Source.txt中读取内容到缓冲区
    NamedPipe pipe ;
    pipe.Create(PIPE_FILE) ;
    pipe.OpenForWrite(PIPE_FILE);
    int infd = open("Source.txt" , O_RDONLY);
    if( infd == -1) 
        ERR_EXIT("open");
    pipe.Write(infd);
    pipe.Destory() ;
    return 0 ;
}
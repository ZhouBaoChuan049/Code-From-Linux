#include "Common.hpp"
int main()
{
    umask(0);
    int n = mkfifo(PIPE_FILE, 0666);
    if (n == -1)
        ERR_FIFO("mkfifo");
    int wfd = open(PIPE_FILE, O_WRONLY);
    if (wfd == -1)
        ERR_FIFO("mkfifo");
    else
    {
        while (true)
        {
            std::cout<<"#PleaseEnter:";
            std::cout.flush();
            char buffer [1024] ;
            memset(buffer , 0 , sizeof(buffer));
            int m = read( 0 ,buffer ,sizeof(buffer));
            if(m < 0 )
                ERR_FIFO("read");
            else
            {
                int i = write(wfd , buffer ,m);
                if(i < 0 ) 
                    ERR_FIFO("write");
            }
        }
    }
    return 0;
}
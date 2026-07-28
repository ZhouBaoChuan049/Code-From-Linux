#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include<unistd.h>
#include<stdlib.h>
void Hander(int x)
{
    std::cout<<"捕捉到信号"<< x << std::endl ;
}
int main()
{
    for(int i = 1 ; i< 32 ; i ++)
        signal(i , Hander);
    for(int i = 1 ; i < 8 ; i ++)    {
        //kill(getpid(),i);
        //raise(i);
        abort();
        sleep(1);
    }
    return 0 ;
}

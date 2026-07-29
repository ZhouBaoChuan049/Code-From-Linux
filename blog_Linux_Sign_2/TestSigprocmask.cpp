#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void PrintfSignpending(sigset_t ped)
{
    std::cout<<"我是进程:["<<getpid()<<"]"<<"我的Pending表是: ";
    for(int i = 1 ; i < 32 ; i++)
    {
        if(sigismember(&ped , i))
            std::cout<<"1";
        else
            std::cout<<"0";
    }
    std::cout<<std::endl; 
}

int main()
{
    sigset_t block;
    sigset_t oblock;
    sigemptyset(&block);
    sigemptyset(&oblock);

    sigaddset(&block, SIGINT);
    sigprocmask(SIG_SETMASK, &block, &oblock);
    while (true)
    {
        sigset_t pending;
        sigpending(&pending);
        PrintfSignpending(pending);
        sleep(1);
    }
    return 0;
}
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void PrintfSignpending(sigset_t ped)
{
    std::cout << "我是进程:[" << getpid() << "]" << "我的Pending表是: ";
    for (int i = 31; i > 0; i--)
    {
        if (sigismember(&ped, i))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << std::endl;
}
void Hander(int n)
{
    std::cout<< "信号"<<n<<"已递达"<<std::endl;
}
int main()
{
    signal(SIGINT,Hander);
    int count = 5 ;
    sigset_t block;
    sigset_t oblock;
    sigemptyset(&block);
    sigemptyset(&oblock);
    sigaddset(&block, SIGINT);
    sigprocmask(SIG_SETMASK, &block, &oblock);
    sigset_t pending;
    raise(SIGINT);
    while (true)
    {
        if(count == 0)
        {
            sigset_t nblock;
            sigemptyset(&nblock);
            sigprocmask(SIG_SETMASK, &nblock, &oblock);
            count = -1;
        }
            
        sigpending(&pending);
        PrintfSignpending(pending);
        sleep(1);
        if(count > 0)
            count --;
    }
    return 0;
}
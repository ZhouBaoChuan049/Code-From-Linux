#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
void WaitAll(int num)
{
    while (true)
    {
        pid_t n = waitpid(-1, nullptr, WNOHANG);
        if(n == 0)
        {
            break;
        }
        else if(n < 0)
        {
            std::cout << "waitpid error " << std::endl;
            break;
        }
    }

    std::cout << "father get a signal: " << num << std::endl;
}
int main()
{
    signal(SIGCHLD, WaitAll);
    int pid = fork();
    if (pid == 0)
    {
        std::cout<<"I am a child new I will exit"<<std::endl;
        sleep(3);
        exit(300);
    }
    std::cout<<"I am Futher I will exit"<<std::endl;
    return 0;
}
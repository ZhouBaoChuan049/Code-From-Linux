#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <string>

using namespace std;

void FuncZombie()
{
    pid_t id = fork();
    if(id < 0)
    {
        string strerror("fork fail");
        throw strerror;
    }
    else if(id == 0)
    {
        int count = 5;
        while(count)
        {
            cout << "我是一个子进程，我的PID是：" << getpid() << endl;
            sleep(1);
            count--;
        }
    }
    else if(id > 0)
    {
        while(true)
        {
            cout << "我是一个父进程，我的PID是：" << getpid() << endl;
            sleep(1);
        }
    }
}

void FuncOrphan()
{
    pid_t id = fork();
    if(id < 0)
    {
        string strerror("fork fail");
        throw strerror;
    }
    else if(id == 0)
    {
        while(true)
        {
            cout << "我是一个子进程，我的PID是：" << getpid() << "，我的PPID是：" << getppid() << endl;
            sleep(1);
        }
    }
    else if(id > 0)
    {
        int count = 5;
        while(count)
        {
            cout << "我是一个父进程，我的PID是：" << getpid() << endl;
            sleep(1);
            count--;
        }
    }
}

int main()
{
    try {
        FuncZombie();
       //FuncOrphan();	
    } catch (string& e) {
        cout << e << endl;
    }
    return 0;
}

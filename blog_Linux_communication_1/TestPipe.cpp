#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<cstdio>
#include<cstring>
void child_write(int wfd)
{
    int cnt =0 ;
    while(1){
        char buffer[1024] = {0} ;
        snprintf(buffer , sizeof(buffer),
        "我是子进程，我的pid是：%d ，我的计数器目前是：%d" , getpid(),cnt++);
        sleep(1);
        int realwrite = write(wfd , buffer , strlen(buffer));
    }
}
void futher_read(int rfd)
{
    char buf [1024*2] ={0};
    while(1)
    {
        memset(buf,0,sizeof(buf));
        int realread = read(rfd,buf,sizeof(buf));
        buf[realread] =0;
        std::cout<<buf<<std::endl;
    }
}
int main()
{
    int pipefd[2] = {0};
    int ret = pipe(pipefd);
    if (ret == 0)
    {
        // 创建管道成功！
        int id = fork();
        if (id == 0)
        {
            // 子进程
            close(pipefd[0]);
            //code of child
            child_write(pipefd[1]);
            close(pipefd[1]);
        }
        // 父进程
        close(pipefd[1]);
        //code of futher
        futher_read(pipefd[0]);
        close(pipefd[0]);
        int statue = 0;
        int rid = waitpid(id,&statue,0);
    }
    return 0;
}

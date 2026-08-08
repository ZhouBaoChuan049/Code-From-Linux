#include <iostream>
#include <pthread.h>
#include <vector>
#include<unistd.h>
int ticket = 100000;
pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t _cond = PTHREAD_COND_INITIALIZER;
void *RunThread(void *args)
{
    char *name = static_cast<char *>(args);
    while (true)
    {
        {
            pthread_mutex_lock(&_mutex);
            pthread_cond_wait(&_cond,&_mutex);
            if (ticket > 0)
            {
                ticket--;
                std::cout<<"线程"<<name<<"抢到票: "<<ticket<<std::endl;
            }
            pthread_mutex_unlock(&_mutex);
        }
    }
}

int main()
{
    int cnt = 5;
    std::vector<pthread_t> pvr ;
    while (cnt)
    {
        pthread_t tid;
        pvr.push_back(tid);
        char *name = new char[64];
        int n = snprintf(name, 64, "thread-%d", cnt);
        if (n < 0)
            perror("snprintf error");
        pthread_create(&tid, nullptr, RunThread, name);
        cnt--;
    }
    //sleep(3);
    while(true)
    {
        std::cout<<"唤醒一个线程"<<std::endl;
        usleep(1000);
        pthread_cond_signal(&_cond);
    }
    for(auto e : pvr)
    {
        pthread_join(e,nullptr);
    }
    return 0;
}
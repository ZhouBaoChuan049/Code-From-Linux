#include "BlockQueue.hpp"
#include "Task.hpp"
// Producer-Consumer Problem
const size_t THREAD_SIZE = 5;
class ThreadData
{
public:
    ThreadData(MyBlockQueue::BlockQueue<task_t>* bqueue , char* name)
        :_bqueue(bqueue)
        ,_name(name)
    {}

    MyBlockQueue::BlockQueue<task_t>* _bqueue ;
    char* _name ;
};
void *Produce(void *args)
{
    MyBlockQueue::BlockQueue<task_t>* _bqueue = 
    static_cast<ThreadData*>(args)->_bqueue ;
    while(true)
    {
        std::cout<<"生产一个任务"<<std::endl;
        _bqueue->Equeue(DownLoadTask);
    }
    delete[](static_cast<ThreadData*>(args)->_name) ;
}
void *Consumer(void *args)
{
    sleep(3);
    MyBlockQueue::BlockQueue<task_t>* _bqueue = 
    static_cast<ThreadData*>(args)->_bqueue ;
    while(true)
    {
        std::cout<<"消费一个任务"<<std::endl;
        task_t task = _bqueue->Pop();
        task();
    }
    delete[](static_cast<ThreadData*>(args)->_name) ;
}
int main()
{
    std::vector<pthread_t> pnums;
    std::vector<pthread_t> cnums;
    MyBlockQueue::BlockQueue<task_t>* bqueue = new MyBlockQueue::BlockQueue<task_t>() ;
    
    // 生产者创建
    for (int i = 0; i < THREAD_SIZE; i++)
    {
        pthread_t tid = 0;
        char *name = new char[64];
        int n = snprintf(name, 64, "PThread-%d", i);
        (void)n;
        ThreadData* data = new ThreadData(bqueue , name);
        pthread_create(&tid, nullptr, Produce, data);
        pnums.push_back(tid);
    }
    // 消费者创建
    for (int i = 0; i < THREAD_SIZE; i++)
    {
        pthread_t tid = 0;
        char *name = new char[64];
        int n = snprintf(name, 64, "CThread-%d", i);
        (void)n;
        ThreadData* data = new ThreadData(bqueue , name);
        pthread_create(&tid, nullptr, Consumer, data);
        cnums.push_back(tid);
    }
    // 回收生产者
    for (auto e : pnums)
    {
        pthread_join(e,nullptr);
    }
    //回收消费者
    for (auto e : cnums)
    {
        pthread_join(e,nullptr);
    }
    return 0;
}
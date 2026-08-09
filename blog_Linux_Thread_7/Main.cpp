#include"RingQueue.hpp"
#include"Task.hpp"
#include<ctime>
using namespace ProducerAndConsumerProblemByRingQueue ;
const size_t THREAD_NUM = 5 ;
class ThreadData
{
public:
    ThreadData(RingQueue<task_t>* ringqueue , char* name)
        :_ringqueue(ringqueue)
        ,_name(name)
    {}
    RingQueue<task_t>* _ringqueue ;
    char* _name ;
};
task_t RandTask()
{
    TaskManager tmang ;
    tmang.Register(MemaryProblem);
    tmang.Register(SQLProblem);
    tmang.Register(InternetProblem);
    return tmang[rand()%TASK_NUM];
}
void* Producer(void* args)
{
    char* name = static_cast<ThreadData*>(args)->_name ;
    RingQueue<task_t>* ringqueue = 
    static_cast<ThreadData*>(args)->_ringqueue ;
    while(true)
    {
        std::cout<< name <<"生产一个任务 "<<std::endl;
        ringqueue->Equeue(RandTask());
    }
    delete[](static_cast<ThreadData*>(args)->_name);
}
void* Consumer(void* args)
{
    char* name = static_cast<ThreadData*>(args)->_name ;
    RingQueue<task_t>* ringqueue = 
    static_cast<ThreadData*>(args)->_ringqueue ;
    while(true)
    {
        std::cout<< name <<"消费一个任务 "<<std::endl;
        task_t task = ringqueue->Pop();
        task();
    }
    delete[](static_cast<ThreadData*>(args)->_name);
}
int main()
{
    srand((unsigned int) time(NULL));
    std::vector<pthread_t> p_thread ;
    std::vector<pthread_t> c_thread ;
    RingQueue<task_t>* ringqueue = new RingQueue<task_t>();
    //生产者们
    for(int i = 0 ; i < THREAD_NUM ; i++)
    {
        char* name = new char[64];
        int n = snprintf(name , 64 , "ProducerThread-%d" , i);
        (void)n ;
        ThreadData* data = new ThreadData(ringqueue , name);
        pthread_t tid;
        pthread_create(&tid , nullptr , Producer , data);
        p_thread.push_back(tid);
    }
    //消费者们
    for(int i = 0 ; i < THREAD_NUM ; i++)
    {
        char* name = new char[64];
        int n = snprintf(name , 64 , "ComsumerThread-%d" , i);
        (void)n ;
        ThreadData* data = new ThreadData(ringqueue , name);
        pthread_t tid;
        pthread_create(&tid , nullptr , Consumer , data);
        c_thread.push_back(tid);
    }
    for(auto e : p_thread)
        pthread_join(e , nullptr);
    for(auto e : c_thread)
        pthread_join(e ,nullptr);
    return 0 ;
}
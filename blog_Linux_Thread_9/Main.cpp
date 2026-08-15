#include "ThreadPool.hpp"
using namespace LogModule ;
using namespace ThreadPoolModuleBasedOnSingletonPattern;

const size_t NUM = 5 ;
int main()
{
    ENABLE_FILE_LOG_STRATEGY();
    for(int i = 0 ; i < NUM ;i ++)
    {
        sleep(1);
        ThreadPool<task_t> :: GetInstance()->Equeue(DownLoadTask);
    }
    ThreadPool<task_t> :: GetInstance()->Stop();
    ThreadPool<task_t> :: GetInstance()->Join();
    return 0;
}
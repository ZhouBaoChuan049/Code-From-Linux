#include "MyThread.hpp"

class ThreadData
{
private:
    std::string _name;
    pthread_t _tid;
};

int main()
{
    ThreadData tda;
    MyThread::Thread<ThreadData> thread_1(tda, [](ThreadData td)
    { std::cout << "线程正在执行任务1" << std::endl; sleep(1);});
    MyThread::Thread<ThreadData> thread_2(tda, [](ThreadData td)
    { std::cout << "线程正在执行任务2" << std::endl; sleep(1);});
    MyThread::Thread<ThreadData> thread_3(tda, [](ThreadData td)
    { std::cout << "线程正在执行任务3" << std::endl; sleep(1);});
    MyThread::Thread<ThreadData> thread_4(tda, [](ThreadData td)
    { std::cout << "线程正在执行任务4" << std::endl; sleep(1);});
    thread_1.Start();
        thread_2.Start();
            thread_3.Start();
                thread_4.Start();
    thread_1.Stop();
        thread_2.Stop();
            thread_3.Stop();
                thread_4.Stop();
    thread_1.Join();
        thread_2.Join();
            thread_3.Join();
                thread_4.Join();
    return 0;
}
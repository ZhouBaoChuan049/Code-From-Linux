#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <vector>
#include<functional>
using Task = std::function<void(void)> ;
class TaskManager{
private:
    std::vector<Task> Taskv;
public:
    TaskManager(){};
    ~TaskManager(){};
    void Addtask(const std::function<void(void)>& task){
        Taskv.push_back(task);
    }
    Task Gettask(int i){
        return Taskv[i];
    }
};

void *Routine(void *args)
{
    Task* task = (Task*) args ;
    (*task)();
    delete task ;
    // for (int i = 0; i < 10; i++)
    //     std::cout << "我是一个线程" << "我的名字是" << args << "我的tid是" << pthread_self() << std::endl;
    return (void *)100;
}
void func_1() { std::cout << "线程 [" << pthread_self() << "] 正在执行：网络任务" << std::endl; }
void func_2() { std::cout << "线程 [" << pthread_self() << "] 正在执行：数据库任务" << std::endl; }
void func_3() { std::cout << "线程 [" << pthread_self() << "] 正在执行：系统任务" << std::endl; }
void func_4() { std::cout << "线程 [" << pthread_self() << "] 正在执行：重要任务" << std::endl; }
void func_5() { std::cout << "线程 [" << pthread_self() << "] 正在执行：关键任务" << std::endl; }
int main()
{
    TaskManager taskmag ;
    taskmag.Addtask(func_1);
    taskmag.Addtask(func_2);
    taskmag.Addtask(func_3);
    taskmag.Addtask(func_4);
    taskmag.Addtask(func_5);


    std::vector <pthread_t> pvtion ={0};
    for (int i = 0; i < 5; i++)
    {
        Task* task = new Task(taskmag.Gettask(i)); 
        int n = pthread_create(&pvtion[i], NULL, Routine, task);
        if (n != 0)
            std::cerr << "pthread_create error" << std::endl;
    }
    for (int i = 0; i < 5; i++)
    {
        void *ret = 0;
        pthread_join(pvtion[i], &ret);
        std::cout << (long)ret << std::endl;
    }
    return 0;
}
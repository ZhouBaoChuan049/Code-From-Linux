#ifndef __TASK__
#define __TASK__
#include<functional>
#include<iostream>
using task_t = std::function<void(void)>;

void DownLoadTask(void)
{
    std::cout<<"这是一个下载任务"<<std::endl;
}
#endif
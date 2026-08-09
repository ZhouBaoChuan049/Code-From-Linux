#pragma once 
#include<functional>
using task_t = std::function<void(void)>;

void DownLoadTask(void)
{
    std::cout<<"这是一个下载任务"<<std::endl;
}
#include<iostream>
#include<unistd.h>
#include <signal.h>
#include<time.h>
#include<vector>
#include<functional>
std::vector<std::function<void (int)>> work ;
void func_1(int x) { std::cout << "我是一个网络任务，参数为: " << x << std::endl; }
void func_2(int x) { std::cout << "我是一个磁盘任务，参数为: " << x << std::endl; }
void func_3(int x) { std::cout << "我是一个日志任务，参数为: " << x << std::endl; }
void func_4(int x) { std::cout << "我是一个计算任务，参数为: " << x << std::endl; }
void func_5(int x) { std::cout << "我是一个数据库任务，参数为: " << x << std::endl; }
void Hander(int i )
{
    std::cout<<"###########################"<<std::endl;
    work[rand()%5](rand()%100);
    alarm(1);
    std::cout<<"###########################"<<std::endl;
}
int main()
{
    work.push_back(func_1);
    work.push_back(func_2);
    work.push_back(func_3);
    work.push_back(func_4);
    work.push_back(func_5);
    srand((unsigned int)time(NULL));
    for(int i = 0 ; i < 32 ; i++)
        signal(i,Hander);
    alarm(1);
    //std::cout<<"定一个闹钟"<<std::endl;
    //std::cout<<"开始睡觉"<<std::endl;
    while(true)
        pause();
    //std::cout<<"睡醒"<<std::endl;
    return 0 ;
}
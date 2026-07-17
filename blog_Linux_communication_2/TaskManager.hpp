#pragma once
#include<vector>
#include<functional>
#include<ctime>
#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string>
using namespace std ;
void PrintLog(){ cout<< "这是一个打印日志的任务！ " <<endl; }
void BuildInternet(){ cout<<" 这是一个建立网络链接的任务！"<<endl; }
void PrintSQL(){ cout<<"这是一个打印数据库的任务!"<<endl; }
class TaskManager{
public:
    TaskManager()
        :_tasknum(0)
    { 
        srand((unsigned int)time(NULL));
    }
    ~TaskManager(){}
    void Register(const function<void()>& func){
        _func.emplace_back(func);
        _tasknum ++ ;
    }
    int TaskCode(){return rand()%_tasknum ;}//这个code从哪里来是一个问题
    void Execute(int code ) {
        _func[code]();
    }
private:
    int _taskcode ;
    vector<function<void()>> _func ;
    int _tasknum ;
    //任务码和任务体建立kv映射关系
};

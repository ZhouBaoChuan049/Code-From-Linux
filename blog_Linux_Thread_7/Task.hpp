#include<functional>
#include<iostream>
#include <vector>
using task_t = std::function<void(void)>;
const size_t TASK_NUM = 3 ;
void MemaryProblem()
{
    std::cout<<"This is a Memary Problem"<<std::endl;
}
void SQLProblem()
{
    std::cout<<"This is a SQL Problem"<<std::endl;
}
void InternetProblem()
{
    std::cout<<"This is a Internet Problem"<<std::endl;
}
class TaskManager
{
public:
    TaskManager() = default;
    ~TaskManager()
    {}
    void Register(task_t task)
    {
        _TaskCollection.push_back(task);
    }
    task_t operator[] (size_t i)
    {
        return _TaskCollection[i];
    }
private:
    std::vector<task_t> _TaskCollection;
};
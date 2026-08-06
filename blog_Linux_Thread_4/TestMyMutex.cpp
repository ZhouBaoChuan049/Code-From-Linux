#include "MyMutex.hpp"
int ticket = 10000;
MyMutex::Mutex mutex;
void *BuyTicket(void *args)
{
    std::string *name = (std::string *)args;
    std::cout << "I am The Child Thread[" << *name << "]"
              << "My ThreadId is" << pthread_self() << std::endl;
    while (true)
    {
        {
            MyMutex::Mutexgrand mutexgrand(mutex);
            if (ticket > 0)
            {
                usleep(1);
                ticket--;
                std::cout << "进程[" << *name << "]抢到一张票" << "ticket=" << ticket << std::endl;
                continue;
            }
            if(ticket<=0)
            {
                break;
            }
        }
    }
    return nullptr;
}
int main()
{
    std::vector<pthread_t> ptd;
    for (int i = 0; i < 5; i++)
    {
        pthread_t tid = 0;
        std::string *name = new std::string("Thread" + std::to_string(i));
        pthread_create(&tid, NULL, BuyTicket, name);
        ptd.push_back(tid);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(ptd[i], nullptr);
    }
}
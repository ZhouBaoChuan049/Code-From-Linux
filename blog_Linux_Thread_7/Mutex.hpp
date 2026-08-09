#pragma once
#include <pthread.h>
namespace MyMutex
{
    class Mutex
    {
    public:
        Mutex()
        {
            pthread_mutex_init(&_mutex,nullptr);
        }
        void Lock()
        {
            pthread_mutex_lock(&_mutex);
        }
        void UnLock()
        {
            pthread_mutex_unlock(&_mutex);
        }
        ~Mutex()
        {
            pthread_mutex_destroy(&_mutex);
        }
    private:
        pthread_mutex_t _mutex ;
    };
}

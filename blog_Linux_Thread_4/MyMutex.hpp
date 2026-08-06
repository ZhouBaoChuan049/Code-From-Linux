#pragma once
#include <iostream>
#include <pthread.h>
#include <string>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#include <unistd.h>
namespace MyMutex{
    class Mutex
    {
    public:
        Mutex()
        {
            pthread_mutex_init(&_lock,nullptr);
        }
        void Lock()
        {
            pthread_mutex_lock(&_lock);
        }
        void Unlock()
        {
            pthread_mutex_unlock(&_lock);
        }
        ~Mutex()
        {
            pthread_mutex_destroy(&_lock);
        }
    private:
        pthread_mutex_t _lock ;
    };
    class Mutexgrand
    {
    public:
        Mutexgrand(Mutex& mutex)
            :_mutex(mutex)
        {
            _mutex.Lock();
        }
        ~Mutexgrand()
        {
            _mutex.Unlock();
            
        }
    private:
        Mutex& _mutex;
    };
}
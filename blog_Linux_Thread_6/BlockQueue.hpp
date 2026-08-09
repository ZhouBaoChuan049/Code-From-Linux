#pragma once
#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<queue>
#include<cstdio>
const size_t DEFULT_CAPACITY  = 5;
namespace MyBlockQueue
{
    template<class T>
    class BlockQueue
    {
    private:
        bool IsFull()
        {
            return _queue.size() == _capacity ;
        }
        bool IsEmpty()
        {
            return _queue.empty();
        }
    public:
        BlockQueue(int cap = DEFULT_CAPACITY)
            :_capacity(cap)
            ,sleep_c(0)
            ,sleep_p(0)
        {
            pthread_mutex_init(&_mutex,nullptr);
            pthread_cond_init(&_cond_c,nullptr);
            pthread_cond_init(&_cond_p,nullptr);
        }
        void Equeue(const T& args)
        {
            //生产者调用
            pthread_mutex_lock(&_mutex);
            while(IsFull())
            {
                std::cout<<"生产者进入休眠 sleep_p = "<<sleep_p<<std::endl;
                sleep_p ++ ;
                pthread_cond_wait(&_cond_p,&_mutex);
                sleep_p -- ;
            }
            _queue.push(args);
            if(sleep_c != 0)
            {
                pthread_cond_signal(&_cond_c);
            }
            pthread_mutex_unlock(&_mutex);
        }
        T Pop()
        {
            //消费者调用
            pthread_mutex_lock(&_mutex);
            while(IsEmpty())
            {
                std::cout<<"消费者进入休眠 sleep_c = "<<sleep_c<<std::endl;
                sleep_c ++ ;
                pthread_cond_wait(&_cond_c,&_mutex);
                sleep_c -- ;
            }
            T _data = _queue.front();
            _queue.pop();

            if(sleep_p != 0)
            {
                pthread_cond_signal(&_cond_p);
            }
            pthread_mutex_unlock(&_mutex);
            return _data ;
        }
        ~BlockQueue()
        {
            pthread_mutex_destroy(&_mutex);
            pthread_cond_destroy(&_cond_p);
            pthread_cond_destroy(&_cond_c);
        }
    private:
        std::queue<T> _queue ;
        size_t _capacity ;
        pthread_mutex_t _mutex ;
        pthread_cond_t _cond_p ;
        pthread_cond_t _cond_c ;
        size_t sleep_c ;
        size_t sleep_p ;
    };
}
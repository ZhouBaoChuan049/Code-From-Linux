#pragma once
#include <unistd.h>
#include <cstdio>
#include <vector>
#include "Mutex.hpp"
#include "Sem.hpp"
using namespace MySem;
using namespace MyMutex;
const size_t DEFULT_SIZE = 5;
namespace ProducerAndConsumerProblemByRingQueue
{
    template <typename T>
    class RingQueue
    {
    public:
        RingQueue(size_t N = DEFULT_SIZE)
            : _capacity(N), _blank_sem(N), _data_sem(0), _c_step(0), _p_step(0)
        {
            _RingQueue.resize(_capacity);
        }
        void Equeue(const T& args)
        {
            //Producer
            _blank_sem.P();
            {
                _p_mutex.Lock();
                _RingQueue[_p_step] = args ;
                _p_step++;
                _p_step %= _capacity ;
                _data_sem.V();
                _p_mutex.UnLock();
            }
        }
        T Pop()
        {
            //Consumer
            T data ;
            _data_sem.P();
            {
                _c_mutex.Lock();
                data = _RingQueue[_c_step];
                _c_step++;
                _c_step %= _capacity ;
                _blank_sem.V();
                _c_mutex.UnLock();
            }
            return data;
        }
        ~RingQueue()
        {}
    private:
        std::vector<T> _RingQueue;
        size_t _capacity;

        Sem _blank_sem;
        Sem _data_sem;

        size_t _c_step;
        size_t _p_step;

        Mutex _c_mutex;
        Mutex _p_mutex;
    };
}

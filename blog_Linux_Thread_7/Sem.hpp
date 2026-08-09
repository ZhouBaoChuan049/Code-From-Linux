#pragma once
#include <semaphore.h>
namespace MySem
{
    class Sem
    {
    public:
        Sem(size_t size)
        {
            sem_init(&_sem, 0, size);
        }
        void P()
        {
            sem_wait(&_sem);
        }
        void V()
        {
            sem_post(&_sem);
        }
        ~Sem()
        {
            sem_destroy(&_sem);
        }

    private:
        sem_t _sem;
    };
}
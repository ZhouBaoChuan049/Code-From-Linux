#pragma once
#include <iostream>
#include <pthread.h>
#include <string>
#include <cstdio>
#include <cstring>
#include <functional>
#include<unistd.h>
namespace MyThread{
    uint32_t number = 1;
    template <typename T>
    class Thread{
        using func_t = std::function<void(T)>;
    private:
        void enablerunning(){
            _isrunning = true;
        }
        void enabledetach(){
            _isdetach = true;
        }
        static void*routine(void* args)
        {
            Thread<T>* self = (Thread<T>*) args ;
            self->_isrunning = true ;
            self->_func(self->_data);
            return nullptr ;
        } 
    public:
        Thread(T data , func_t func)
            : _tid(0), _isrunning(false), _isdetach(false), _ret(nullptr), _func(func), _data(data){
            _name = "Thread-" + std::to_string(number++);
        }
        ~Thread() {}
        bool Start(){
            if (_isrunning)
                return false;
            int n = pthread_create(&_tid, nullptr, routine, this);
            if (n == 0){
                std::cout << "线程[" << _name << "]创建成功" << std::endl;
                return true;
            }
            else{
                std::cout << "线程[" << _name << "]创建失败" << std::endl;
                return false;
            }
            return false;
        }
        bool Detach(){
            if (!_isdetach){
                int n = pthread_detach(_tid);
                if (n == 0){
                    std::cout << "线程[" << _name << "]分离成功" << std::endl;
                    _isdetach = true ;
                    return true;
                }
                else{
                    std::cout << "线程[" << _name << "]分离失败" << std::endl;
                    return false;
                }
            }
            return false;
        }
        bool Stop(){
            if (_isrunning){
                int n = pthread_cancel(_tid);
                if (n == 0){
                    std::cout << "线程[" << _name << "]取消成功" << std::endl;
                    _isrunning = false;
                    return true;
                }
                else{
                    std::cout << "线程[" << _name << "]取消失败" << std::endl;
                    return false;
                }
            }
            return false;
        }
        bool Join(){
            if (_isdetach){
                std::cout << "线程[" << _name << "]为分离线程，不可被主动回收" << std::endl;
                return false;
            }
            if (_isrunning){
                int n = pthread_join(_tid, &_ret);
                if (n == 0){
                    std::cout << "线程[" << _name << "]回收成功" << std::endl;
                    _isrunning = false;
                    return true;
                }
                else{
                    std::cout << "线程[" << _name << "]回收失败" << std::endl;
                    return false;
                }
            }
            return false;
        }
    private:
        pthread_t _tid;
        bool _isrunning;
        bool _isdetach;
        void *_ret;
        func_t _func;
        T _data;
        std::string _name;
    };
}
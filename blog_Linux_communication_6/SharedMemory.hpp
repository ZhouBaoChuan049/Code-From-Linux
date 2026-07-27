#pragma once
#include "Comman.hpp"
class SharedMemory{
private:
    void CreateHelp(const int Mode ){
        _shmid = shmget(_key , _size , Mode);
        if(_shmid == -1) ERR_MEMORY("创建共享内存失败");
    }
    void CreateMemory(){ 
        umask(0);
        CreateHelp(IPC_CREAT | IPC_EXCL | 0666 ) ;
        std::cout<<"创建共享内存成功！" << std::endl ;
    }
    void GetMemory(){ 
        CreateHelp(IPC_CREAT | 0666 ) ;
        std::cout<<"获取共享内存成功！" << std::endl ;
    }
    void AttachFunc(){
        _StartMemory = (char*)shmat(_shmid , nullptr ,0 );
        if(_StartMemory == (char*)-1) 
            ERR_MEMORY("虚拟-物理内存关联失败") ;
        std::cout<<"创建虚拟-物理内存关联成功"<<std::endl ;
    }
    void DetachFunc(){
        if (_StartMemory != nullptr) {
            int n = shmdt(_StartMemory);
            if (n == -1) 
                std::cerr << "【错误】取消虚拟-物理内存关联失败: " << strerror(errno) << std::endl;
            else {
                std::cout << "取消虚拟-物理内存关联成功" << std::endl;
                _StartMemory = nullptr; 
            }
        }
    }
    void DestoryMemory(){
        int n = shmctl(_shmid, IPC_RMID, nullptr);
        if (n == -1) 
            std::cerr << "【错误】销毁共享内存失败: " << strerror(errno) << std::endl;
        else 
            std::cout << "回收共享内存成功" << std::endl;
    }
public:
    SharedMemory(int identity , int key ,int size)
        :_key(key)
        ,_size(size)
        ,_shmid(0)
        ,_StartMemory(nullptr)
        ,_identity(identity){
        if (identity == SERVER)
            CreateMemory();
        else if (identity == CLIENT)
            GetMemory();
        else ERR_MEMORY("未知身份创建共享内存") ;
    }
    void AttachMemory(){ AttachFunc(); }
    ~SharedMemory(){
        DetachFunc() ;
        if(_identity == SERVER) {
            DestoryMemory() ;
        }
    }
    char* GetStartMemory() { 
        std::cout<<"获取共享内存首地址成功"<<std::endl ;
        return _StartMemory ; 
    }
    const int GetSize(){
        std::cout<<"获取共享内存大小成功"<<std::endl ; 
        return _size ; 
    }
private:
    int _shmid ;
    const key_t _key ;
    const int _size ;
    char* _StartMemory ;
    int _identity ;
};
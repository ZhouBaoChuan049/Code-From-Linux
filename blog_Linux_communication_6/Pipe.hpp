#pragma once
#include "Comman.hpp"
class NamedPipe{
public:
    NamedPipe(std ::string file = PIPE_FILE)
        :_file(file){
        umask(0);
        int n = mkfifo(file.c_str(), 0666);
        if (n == -1)
            ERR_MEMORY("创建管道失败");
        else
            std::cout<<"创建管道成功"<<std::endl;
    }
    ~NamedPipe(){
        int n = unlink(_file.c_str());
        if (n == -1)
            std::cerr << "【错误】销毁管道失败: " << strerror(errno) << std::endl;
        std::cout<<"销毁管道成功"<<std::endl;
    }
private:
    std ::string _file ;
};
class PipeOper{
private:
    void OpenHelp(int Mode,std ::string file = PIPE_FILE){
        _pipefd = open(file.c_str(), Mode);
        if (_pipefd == -1 && Mode == O_RDONLY)
            ERR_MEMORY("以读取方式打开管道失败");
        else if (_pipefd == -1 && Mode == O_WRONLY)
            ERR_MEMORY("以写入方式打开管道失败");
        else
            std::cout<<"以打开管道成功"<<std::endl;
    }
public:
    PipeOper(){}
    ~PipeOper(){}
    void OpenForRead(std ::string file = PIPE_FILE){ OpenHelp(O_RDONLY,PIPE_FILE); }
    void OpenForWrite(std ::string file = PIPE_FILE){ OpenHelp(O_WRONLY,PIPE_FILE); }
    void Close(){ close(_pipefd); }
    int Wait(){
        int sign = 0 ;
        int n = read(_pipefd , &sign, sizeof(sign));
        if(n == -1) 
            ERR_MEMORY("信道读取失败");
        else if(n == 0)
            return 0 ;
        // else
        //    std::cout<<"信道读取成功"<<std::endl;
        return sign ;
    }
    void WeakUp(){
        int sign = GETUP ;
        int n  = write(_pipefd , &sign , sizeof(sign));
        if(n == -1)
            ERR_MEMORY("信道写入失败");
        std::cout<<"信道写入成功"<<std::endl;
    }
private:
    int _pipefd ;
};
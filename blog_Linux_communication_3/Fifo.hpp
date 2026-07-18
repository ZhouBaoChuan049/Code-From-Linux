#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sys/stat.h>
class NamedPipe
{
public:
    NamedPipe(std::string path, std::string name)
        : _path(path), _name(name)
    {
        _pipename = _path + name;
        int n = mkfifo(_pipename.c_str(), 0666);
        if (n == 0)
            std::cout << "管道创建成功" << std::endl;
        else
            std::cerr << "管道创建失败" << std::endl;
    }
    ~NamedPipe()
    {
        unlink(_pipename.c_str());
        std::cout << "管道销毁成功" << std ::endl;
    }
private:
    std ::string _path;
    std ::string _name;
    std::string _pipename;
};
class PipeOpt
{
public:
    PipeOpt()
    {}
    ~PipeOpt()
    {}

private:
};

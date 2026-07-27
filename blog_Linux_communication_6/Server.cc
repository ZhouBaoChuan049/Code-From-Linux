#include "Pipe.hpp"
#include "SharedMemory.hpp"
int main(){
    try{
        SharedMemory Shm(SERVER, MemKey, 1024 * 4);
        Shm.AttachMemory();
        NamedPipe fifo(PIPE_FILE);
        PipeOper pipeopt;
        pipeopt.OpenForRead();
        const char* address = Shm.GetStartMemory();
        while(true){
            if(pipeopt.Wait() ==GETUP){
                printf("%s\n",address);
            }
            else if(pipeopt.Wait() == 0)
                break;
        }
        pipeopt.Close();
    }
    catch (std::string _error){
        std::cout << _error << std::endl;
    }
    catch (...){
        std::cout << "未知异常" << std::endl;
    }
    return 0;
}
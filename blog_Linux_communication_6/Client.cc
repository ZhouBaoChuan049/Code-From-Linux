#include "Pipe.hpp"
#include "SharedMemory.hpp"
int main(){
    try{
        SharedMemory Shm(CLIENT , MemKey ,1024*4) ; 
        Shm.AttachMemory();
        PipeOper pipeopt ;
        pipeopt.OpenForWrite(PIPE_FILE);
        char* address = Shm.GetStartMemory();
        int cnt = 26 ;
        int j = 0 ;
        for(int i = 0 ; i < cnt*2 ; i+=2 ){
            address[i] = j+65 ;
            address[i+1] = j+65 ; 
            address[i+2] = '\0';
            pipeopt.WeakUp();
            sleep(1) ;
            j++;
        }
    }
    catch(std::string _error){
        std::cout<<_error<<std::endl;
    }
    catch(...){
        std::cout<<"未知异常"<<std::endl;
    }
    return 0 ;
}
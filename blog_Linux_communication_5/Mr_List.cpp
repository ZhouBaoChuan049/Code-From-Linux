#include "Common.hpp"
int main()
{
    int rfd = open(PIPE_FILE ,O_RDONLY );
    if(rfd == -1) 
        ERR_FIFO("open");
    while(true){
        char buffer[1024] ;
        memset(buffer , 0  , sizeof(buffer)) ;
        std::cout<< "#PleaseWait ..."<<std::endl;
        int n = read(rfd , buffer ,sizeof(buffer)-1) ; 
        if(n < 0 )
            ERR_FIFO("read") ;
        else if(n == 0 ){
            std:: cout<<"Mr_Zhang Hang Up The Telephone！"<<std::endl;
            break;
        }
        else{
            buffer[n] = '\0' ;
            std :: cout << "Mr_Zhang say :"<<buffer ;
        }    
    }
    return 0 ;
}
#include<iostream>
#include<string>
#include<signal.h>
#include<unistd.h>
void Hander(int n){
    std::cout<<"收到信号："<<n << std::endl;
    exit(1);
}
int main(){
    for(int i = 0 ; i < 32 ; i++)
        signal(i , Hander);
    while(1){
        std::cout<<"进程运行中。。。"<<std::endl;
        sleep(1);
    }
    return 0 ;
}
#include "ProcessPool.hpp"
int main(){
    try{
        //创建进程池
        ProcessPool pool(5);
        //启动进程池
        pool.Start();    
        //pool.Debug();
        //利用进程池执行一些任务
        int cnt = 10 ;
        while(cnt){
            pool.Run();
            cnt --;
        }
        //关闭进程池
        pool.Stop();
    }
    catch(string str){
        cout<< str <<endl;
    }
    catch( ... ){
        cout<< "未知的异常" <<endl;
    }
    return 0 ;
}

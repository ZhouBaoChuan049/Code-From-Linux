#ifndef __PROCESS_POOL_
#define __PROCESS_POOL_
#include "TaskManager.hpp"
class Cannel{
public:
    Cannel(int subid , int wfd )
        :_subid(subid)
        ,_wfd(wfd)
        ,_loadnum(0)
    {}
    ~Cannel()
    {}
    void PrintCannel(){
        cout<<"Cannel:"<<_wfd <<"子进程:"<<_subid<<endl;
    }
    int GetSubid(){
        return _subid ;
    }
    int GetWfd(){
        return _wfd ;
    }
    int GetLoadNum(){
        return _loadnum ;
    }
    void Close(){
        close(_wfd);
    }
    void Wait(){
        int statue = 0 ;
        waitpid(_subid , &statue , 0);
    }
private:
    int _subid ;
    int _wfd ;
    int _loadnum ;
};
class CannelManager{
public:
    CannelManager()
        :_cannelnum(0)
        ,_cnt (0)
    {}
    ~CannelManager(){}
    void Insert(pid_t subid , int wfd ){
        _vc.emplace_back(subid,wfd);
        _cannelnum++;
    }
    void PrintDebug(){
        for(auto& e : _vc)
            e.PrintCannel();
    }
    int SelectCannel(){
        return _vc[_cnt++ % _cannelnum].GetWfd();
    }
    void SendTask(int wfd,int taskcode){
        int n = write(wfd , &taskcode ,sizeof(taskcode));
        if(n<0){
            string str("任务发送错误!");
            throw str ;
        }
    }
    void CloseWriteSide(){
        for(auto& e : _vc)
            e.Close();
    }
    void RestoreChildren(){
        for(auto& e : _vc)
            e.Wait();
    }
private:
    vector<Cannel> _vc ;
    int _cannelnum ;
    int _cnt ;
};
class ProcessPool{
public:
    ProcessPool(int num )
        :_CannelNumber(num){
        //注册相关任务
        _tm.Register(PrintSQL);
        _tm.Register(BuildInternet);
        _tm.Register(PrintLog);
    }
    ~ProcessPool(){}
    void Work(int rfd ){
        int code = 0 ;
        while(true){
            int n = read(rfd ,&code ,sizeof(code));
            if(n > 0 ){
                if(n != sizeof(code))
                    continue;
                cout<<"子进程开始执行任务"<<endl;
                _tm.Execute(code);
            }
            else if (n == 0){
                cout<<"未收到任务码，子进程退出"<<endl;
                break;
            }
            else {
                string Exception ("任务码错误,子进程强制退出。");
                throw Exception ;
            }
        }
    }
    void Debug(){
        _cm.PrintDebug();
    }
    void Start(){
        int cnt =_CannelNumber ;
        while(cnt){
            int pipefd [2] ;
            int n = pipe(pipefd);
            if( n  == 0 ){
                pid_t pid = fork();
                if(pid == 0 ){
                    close(pipefd[1]);
                    try{
                        Work(pipefd[0]);
                    }
                    catch(string exc){
                        cout<<"exc"<<endl;
                    }
                    exit(0);
                }
                close(pipefd[0]);
                _cm.Insert(pid , pipefd[1]);
                //所有的释放工作在资源管理器中有单独的封装   
            }
            else cout<<"进程池启动失败"<<endl;
            cnt -- ;
        }
    }
    int SelectTask(){
        return _tm.TaskCode() ;
    }
    void Run(){
        //选择任务
        int taskcode = SelectTask();
        //选择信道
        int wfd = _cm.SelectCannel();
        //发送任务
        _cm.SendTask(wfd , taskcode);
    }
    void Stop(){

        _cm.CloseWriteSide();
        _cm.RestoreChildren();
    }
private:
    CannelManager _cm ;
    TaskManager _tm ; 
    size_t _CannelNumber ; 
};
#endif
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
#include<vector>
#include<functional>
using namespace std;

//方法组
void Func01(){cout<<"父进程执行任务一"<<endl;}
void Func02(){cout<<"父进程执行任务二"<<endl;}
void Func03(){cout<<"父进程执行任务三"<<endl;}


int TestFunc()
{	
	vector<function<void()>> Task;
	Task.push_back(Func01);
	Task.push_back(Func02);
	Task.push_back(Func03);
	pid_t id =fork();
	if(id==0)
	{
		int cnt = 5;
		while(cnt)
		{
			pid_t _pid = getpid();
			cout<<"我是一个子进程"<<"我的PID是:"<<_pid<<endl;
			sleep(1);
			cnt--;
		}
		exit(0);
	}
	sleep(1);
	while(1)
	{
		int statue=0;
		int rid = waitpid(id,&statue,WNOHANG);
		if(rid>0)
		{
			cout<<"等待成功，子进程的退出码为"<< WEXITSTATUS(statue)<<endl;
			break;
		}
		else if(rid==0)
		{
			cout<<"子进程未退出"<<"父进程开始执行任务"<<endl;
			for(const auto& f : Task)
				f();
			sleep(1);
		}
		else
		{
			cout<<"等待失败"<<endl;
			break;
		}

	}
	return 0;
}

int main()
{
	TestFunc();
	return 0;
}


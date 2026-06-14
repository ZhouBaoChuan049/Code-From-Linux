#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
using namespace std;
int Func01()
{
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
	sleep(7);
	pid_t rid = wait(NULL);
	if(rid>0) cout<<rid<<endl;
	sleep(7);
	return 0;
}
int Func02()
{
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
	int statue =0;
	int rid = waitpid(id,&statue,0);
	if(rid > 0)
		cout<<rid<<statue<<endl;
	else
		//cout<<WEXITSTATUS(statue)<<endl;
		//printf("%d \n",(statue>>8)&0xFF);
		cout<<errno<<strerror(errno)<<endl;
	return 0;
}
int Func03()
{	
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
			cout<<"执行第2次等待"<<"子进程未退出"<<endl;
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
	//Func01();
	//Func02();
	Func03();
	return 0;
}


#include<iostream>
#include<unistd.h>
#include<string>
#include<sys/types.h>
using namespace std;
void Func_Test_Process()
{

	pid_t _id = fork();
	if(_id < 0)
	{
		string strerror("fork fail");
		throw strerror;
	}
	else if(_id == 0)
	{
		while(1)
		{
			printf( "这是一个子进程，子进程的pid是: %d ,子进程的ppid是: %d .\n",getpid(),getppid());
			sleep(1);		 
		}

	}
	else if(_id > 0)
	{

		while(1)
		{
			printf( "这是一个父进程，父进程的pid是: %d ,父进程的ppid是: %d .\n",getpid(),getppid());
			sleep(1);
		}		 
	}
}
int main()
{
	try
	{
		Func_Test_Process();
	}
	catch(string&& str)
	{
		cout<<str<<endl;
	}

}


#include<iostream>
#include<cstdio>
#include<cstring>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;
char* newenv = (char* ) "MyEnv=11223344";
void Func()
{

	pid_t id = fork();
	if(id==0)
	{
		putenv(newenv);
		extern char** environ;
		char* _argv[]={(char*)"other",NULL};
		//execv("/bin/ls",_argv);
		//execl("/bin/ls","ls","-a","-l",NULL);
		//execlp("ls","-a","-l",NULL);
		//execlp("./myscript.py","myscript.py",NULL);
		execvpe("./other",_argv,environ);
		exit(0);
	}
	int status = 0;
	pid_t rid = waitpid(id, &status , 0);
	if(rid > 0)
		cout<<"子进程退出成功过"<<"退出码是："<<WEXITSTATUS(status)<<endl;
	else if(rid == 0 )
		cout<<"子进程未退出"<<endl;
	else if(rid < 0)
		cout<<"子进程退出异常"<<endl;

}

int main()
{
	Func();
	return 0;
}


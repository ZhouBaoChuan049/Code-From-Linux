#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>
#include<cstdio>
using namespace std;
#define COMMAND_SIZE 1024
#define COMMANDLINE "[%s@%s %s]# "

int g_argc=0;
char* g_argv[128] = {0};

const char* GetUserName()
{
	const char* name = getenv("USER");
	return name == nullptr? "None" : name;
}
const char* GetHostName()
{
	const char* host =getenv("HOSTNAME");
	return host==nullptr? "None" :host;
}

string GetDirName(const char* pwd)
{
#define SEP "/"
	string str = pwd;
	if(str == SEP) return "/";
	auto e = str.rfind(SEP);
	if(e==string::npos) return "BUG?";
	return str.substr(e+1);

}
string GetCwd()
{
	const char* pwd = getenv("PWD");
	if(pwd==NULL)return "None";
	return GetDirName(pwd);
	//return cwd == nullptr ? "None" : cwd;
}

void MakeCommandLine(char* commandline , int size)
{
	snprintf(commandline,size,COMMANDLINE,GetUserName(),GetHostName(),(GetCwd()).c_str());
}

void PrintCommandLine()
{
	//构建命令行提示符->打印命令行提示符->刷新缓冲区
	char CommandLine [COMMAND_SIZE]={0};
	MakeCommandLine(CommandLine,sizeof(CommandLine));
	//这个MakeCommandLine用了一个输出型参数
	printf("%s",CommandLine);
	fflush(stdout);
}

bool GetCommandLine(char* cml,int size)
{
	char* c = fgets(cml,size,stdin);
	if(c==NULL) return false;
	if(strlen(cml)-1==0) return false;
	cml[strlen(cml)-1]={0};
	return true;
}
void CommandParse(char* cml)
{
#define SPL " "
	g_argc =0;
	g_argv[g_argc++] = strtok(cml,SPL);
	while((bool)(g_argv[g_argc++]=strtok(nullptr,SPL)));
	g_argc--;
}
void Execute()
{
	pid_t _id = fork();
	if(_id==0)
	{
		//子进程执行命令
		execvp(g_argv[0],g_argv);
		exit(0);
	}
	pid_t rid= waitpid(_id,nullptr,0);
	(void ) rid;
	return ;
}

int main()
{
	while(true)
	{
		//打印命令行提示符
		PrintCommandLine();

		//获取用户输入的命令
		char commandline [COMMAND_SIZE] ={0} ;
		if(!GetCommandLine(commandline,sizeof(commandline)))
			continue;
		//命令行分析
		CommandParse(commandline);

		//执行命令
		Execute();
	}

	return 0;
}











































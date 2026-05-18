#include<iostream>
#include<unistd.h>
#include<cstdio>
#include<cstring>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

const int PROMPT_SIZE = 128;
#define PROMPT "[%s@%s %s ]#"

//For Test
#define COMMAND_SIZE 1024
int g_argc = 0;
char* g_argv[COMMAND_SIZE] ={0};

const char* GetUserName()
{
	const char* name = getenv("USER");
	return name==NULL?"None": name;
}

const char* GetHostName()
{
	const char* host = getenv("HOSTNAME");
	return host==NULL?"None": host;
}

string GetDirectory(char* _cwd)
{
	string str = _cwd;
	size_t pos = str.rfind("/");
	if(pos==string :: npos) return "None";
	string ret = str.substr(pos+1);
	return ret;
}

string GetCwd()
{
	char* cwd = getenv("PWD");
	return GetDirectory(cwd);
}

void MakePrompt(char* prompt,int size)
{
	snprintf(prompt,size,PROMPT,GetUserName(),GetHostName(),GetCwd().c_str());
}

void PrintCommandPrompt()
{
	char CommandPrompt[PROMPT_SIZE]={0};
	MakePrompt(CommandPrompt,sizeof(CommandPrompt));
	printf("%s",CommandPrompt);
}

bool GetCommandLine(char* _cmd,int size)
{
	char* ptr = fgets(_cmd , size , stdin);
	if(ptr==NULL) return false;
	_cmd[strlen(_cmd)-1]=0;
	return true;
}
bool AnalyseCommandLine(char* _cmd)
{
#define ESC " "
	g_argc =0;
	g_argv[g_argc++] = strtok(_cmd,ESC);
	while((bool)(g_argv[g_argc++]=strtok(NULL,ESC)));
	g_argc--;
	if(g_argc==0) return false;
	return true;	
}

void Execute()
{
	pid_t _id = fork();
	if(_id==0)
	{
		execvp(g_argv[0],g_argv);
		exit(0);
	}	
	waitpid(_id,nullptr, 0);
	return ;
}
int main()
{
	while(1)
	{
		//打印命令提示符
		PrintCommandPrompt();
		//获取命令行参数
		char CommandLine[COMMAND_SIZE]={0};
		if(!GetCommandLine(CommandLine,sizeof(CommandLine)))
			continue;
		//解析命令行参数
		if(!AnalyseCommandLine(CommandLine))
			continue;
		//执行命令
		Execute();
	}
	return 0;
}


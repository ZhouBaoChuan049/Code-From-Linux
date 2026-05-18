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

//退出码
size_t ExitCode = 0;

//环境变量表
const int ENV_SIZE =100;
int g_envs=0;
char* g_env[ENV_SIZE] ={ 0 };

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

const char* GetHome()
{
	const char* home = getenv("HOME");
	return home ==NULL?"None" : home;
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
	if(strlen(_cmd)==0) return false;
	return true;
}
bool AnalyseCommandLine(char* _cmd)
{
#define ESC " "
	g_argc =0;
	g_argv[g_argc++] = strtok(_cmd,ESC);
	while((bool)(g_argv[g_argc++]=strtok(NULL,ESC)));
	g_argc--;
	return g_argc>0?true:false;	
}

void Execute()
{
	pid_t _id = fork();
	if(_id==0)
	{
		execvp(g_argv[0],g_argv);
		exit(0);
	}	
	int statue = 0;
	pid_t rid = waitpid(_id,&statue, 0);
	if(rid > 0) 
	      ExitCode = WEXITSTATUS(statue);	
	return ;
}
void CommandCd()
{
	if(g_argc == 1)
	{
		chdir(GetHome());
	}
	else if(g_argc == 2)
	{
		if(strcmp(g_argv[1],"-")==0)
			chdir(getenv("OLDPWD"));
		else if(strcmp(g_argv[1],"~")==0)
			chdir(getenv("HOME"));
		else 
			chdir(g_argv[1]);
	}
	else
		cout<<"command not found"<<endl;
}

void CommandEcho()
{
	string What = g_argv[1];
	if(g_argc==2)
	{
		if(What=="$?")
		{
			cout<<ExitCode<<endl;
			ExitCode = 0;
		}
		else if(What[0]=='$')
		{
			string sub = What.substr(1);
			printf("%s",getenv(sub.c_str()));
		}
		else
		{
			cout<<What<<endl;
		}
	}
	else cout<<"command not found"<<endl;
}

bool CheckBuild_inCommand()
{
	string _cmd = g_argv[0];
	if(_cmd == "cd")
	{
		CommandCd();
		return true;
	}
	else if(_cmd == "echo")
	{
		CommandEcho();
		return true;
	}
	else return false;
}

void Initenv()
{
	extern char** environ ;
	memset(g_env,0,sizeof(g_env));
	g_envs = 0;
	//导入到环境变量表
	for(int i = 0 ;environ[i];i++)
	{
		g_env[i] = (char* )malloc(strlen(environ[i])+1);
		strcpy(g_env[i],environ[i]);
		g_envs++;
	}
	g_env[g_envs++]=(char*)"TEST=1234567890";
	g_env[g_envs]=NULL;
	//导出到子shell
	for(int i = 0;g_env[i];i++)
	{
		putenv(g_env[i]);
	}
	environ = g_env;
}


int main()
{
	Initenv();
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
		if(CheckBuild_inCommand())
			continue;
		//执行命令
		Execute();
	}
	return 0;
}


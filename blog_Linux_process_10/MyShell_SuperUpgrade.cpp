#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string>
#include <sys/stat.h>
#include <fcntl.h>
#include <cctype> // 引入 isspace

using namespace std;

const int COMMAND_SIZE = 128;
const int LINE_SIZE = 1024;
#define PROMPT "[%s@%s %s]%s"

const int ENV_SIZE = 100;
int g_envs= 0;
char* g_env[ENV_SIZE] = {0};

#define NONE_REDIR 0
#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3

int redir = NONE_REDIR;
string filename ;

int g_argc = 0;
char* g_argv[LINE_SIZE] = {0}; 

int exitcode = 0; 

const char* GetHostName()
{
	const char* host = getenv("HOSTNAME");
	return host == NULL? "None" : host ;
}

const char* GetUserName()
{
	const char* user = getenv("USER");
	return user == NULL? "None" : user ;
}

string GetDirectory(char* _cwd )
{
	if(_cwd == NULL) return " "; // 增加判空保护防崩溃
	string cwd = _cwd;
	int pos = cwd.rfind("/");
	if(pos == string :: npos )
		return " ";
	return cwd.substr(pos +1);
}

string GetCwd()
{
	char* cwd = getenv("PWD");
	return GetDirectory(cwd); 
}

const char* GetSign()
{
	if(strcmp(GetUserName(), "root") == 0) // 修复：字符串比较
		return "#";
	else return "$";
}

const char* GetHome()
{
	const char* home =  getenv("HOME");
	return home ==NULL? "None" :home;
}

void MakeCommandPrompt(char* det , int size)
{
	snprintf(det,size, PROMPT ,GetUserName(),GetHostName(),GetCwd(),GetSign());
}

void PrintCommandPrompt()
{
	char Prompt[COMMAND_SIZE] = {0};
	MakeCommandPrompt(Prompt,sizeof(Prompt));
	printf("%s",Prompt);
	fflush(stdout);
}

bool GetCommandLine(char* cmd,int size )
{
	char* buf = fgets(cmd , size , stdin);
	if(buf==NULL) return false;
	cmd[(size_t)(strlen(cmd)-1)] = 0;
	if(strlen(cmd)==0) return false;
	return true;
}

void Initenv()
{
	extern char** environ;
	for(int i = 0; environ[i] ; i++)
	{
		g_env[i] = (char*)malloc(strlen(environ[i])+1);
		if(g_env[i]==NULL)
		{
			string enverror("环境变量初始化异常");
			throw enverror;
		}
		strcpy(g_env[i],environ[i]);
		g_envs++;
	}
	g_env[g_envs]=NULL;
	for(int i =0 ;g_env[i];i++)
		putenv(g_env[i]);
}

void RedirCheck(char* cmd)
{
	redir = NONE_REDIR;
	filename.clear();
	int start = 0;
	int end = strlen(cmd) - 1;
	while(end > start)
	{
		if(cmd[end]=='<')
		{
			cmd[end] = 0;
			end++; // 修复：先向后移动一位再跳过空格
			while(isspace(cmd[end]))
				end++;
			redir = INPUT_REDIR; 
			filename = cmd + end;
			break;
		}
		else if(cmd[end]=='>')
		{
			if(cmd[end-1]=='>')//>>
			{
				cmd[end-1] = 0;
				cmd[end] = 0;
				end++; // 修复：向后移动一位再跳过空格
				while(isspace(cmd[end]))
					end++;
				redir = APPEND_REDIR;
				filename = cmd + end;
			}
			else
			{	
				cmd[end] = 0;
				end++; // 修复：向后移动一位再跳过空格
				while(isspace(cmd[end]))
					end++;
				redir = OUTPUT_REDIR;
				filename = cmd + end;
			}
			break;
		}
		else end--;
	}
}

bool AnalyseCommandLine(char* cmd)
{
#define EXC " "
	g_argc = 0;
	g_argv[g_argc++] = strtok(cmd,EXC);
	while((bool)(g_argv[g_argc++]=strtok(NULL,EXC)));
	g_argv[g_argc] = NULL;
	g_argc--;
	if(g_argc==0)
		return false;
	return true;
}

void Cd()
{
	if(g_argc == 1)
		chdir(GetHome());
	else if (g_argc == 2){
		if(strcmp(g_argv[1] ,"~") == 0)
			chdir(GetHome());
		else if(strcmp(g_argv[1],"-")==0)
		{
			const char* oldpwd = getenv("OLDPWD");
			if(oldpwd) chdir(oldpwd);
		}
		else chdir(g_argv[1]);
	}
	else{
		string cderror("cd命令执行错误");
		throw cderror;
	}

	// 维护 PWD 环境变量，防止 cd 后提示符不更新路径
	char cwd_buf[LINE_SIZE];
	if (getcwd(cwd_buf, sizeof(cwd_buf))) {
		setenv("PWD", cwd_buf, 1);
	}
}

void Echo()
{
#define MAX_SIZE_ENV 1000
	if(g_argv[1] == NULL)
	{
		cout << endl;
	}
	else if(strcmp(g_argv[1], "$?") == 0) // 修复：从地址比较改为 strcmp
		cout<<exitcode<<endl;
	else if(g_argv[1][0] == '$')
	{
		const char* tmp = getenv(g_argv[1] + 1); // 修复：利用 +1 跳过 '$' 符号
		if(tmp) cout<< tmp << endl;
		else cout << endl;
	}
	else 
		printf("%s\n",g_argv[1]);
}

bool BuildinCommandCheck()
{
	if(strcmp(g_argv[0] ,"cd") == 0)
	{
		Cd();
		return true;
	}
	else if(strcmp(g_argv[0] , "echo") == 0)
	{
		Echo();
		return true;
	}
	return false; 
}

void Execute()
{
	// 修复：所有的命令执行（包括重定向）统一由子进程进行，防止污染父进程
	pid_t id = fork();
	if(id == 0)
	{
		if(redir == INPUT_REDIR)
		{
			int fd = open(filename.c_str(), O_RDONLY);
			dup2(fd,0);
			close(fd);
		}
		else if(redir == OUTPUT_REDIR)
		{
			int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
			dup2(fd,1);
			close(fd);
		}
		else if(redir == APPEND_REDIR)
		{
			int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);
			dup2(fd,1);
			close(fd);
		}

		execvp(g_argv[0], g_argv);
		exit(1); // 如果 execvp 失败，子进程安全退出
	}

	int statue = 0;
	waitpid(id, &statue, 0);
	if (WIFEXITED(statue)) {
		exitcode = WEXITSTATUS(statue);
	}
}

int main()
{
	try 
	{
		Initenv();
	}
	catch(string error)
	{
		cout<<error<<endl;
	}
	try
	{
		while(true)
		{
			//打印命令行提示符
			PrintCommandPrompt();
			//获取命令行参数
			char commandline[LINE_SIZE] = {0};
			if(!GetCommandLine(commandline ,sizeof(commandline)))
				continue;
			//检测重定向类型
			RedirCheck(commandline);
			//分析命令行参数
			if(!AnalyseCommandLine(commandline))
				continue;	
			//检测是否是内建命令
			if(BuildinCommandCheck())
				continue;
			//执行命令
			Execute();
		}
	}
	catch (string error)
	{
		cout<<error<<endl;
	}
	catch(...)
	{
		cout<<"未知异常"<<endl;
	}
	return 0;
}

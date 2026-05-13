#include <iostream>
#include<stdlib.h>
using namespace std;
extern char** environ;

void Func01(char* env[])
{
    if (env == nullptr) return;

    for (int i = 0; env[i]; i++)
    {
        cout << "env[" << i << "]: " << env[i] << endl;
    }
}
void Func02()
{
	char* _env=getenv("PATH");
	if (_env==NULL) return ;
	printf("PATH->%s",_env);
}
void Func03()
{
	for(int i=0;environ[i];i++)
		cout<<environ[i]<<endl;
}

int main(int argc, char* argv[], char* env[])
{
    (void)argc;
    (void)argv;

    //Func01(env);
      //Func02();
        Func03();
    return 0;
}

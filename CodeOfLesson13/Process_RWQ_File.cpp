#include<iostream>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	chdir("/home/zbc/");
	FILE* fl = fopen("Test_Process.txt","w");
	if(fl!=NULL)
	{
		fprintf(fl, "Ciallo! World\n");
		fclose(fl);
	}
	while(1)
	{
		printf("This is a Process,Pid of him is :%d\n" ,getpid());
		sleep(1);
	}
	return 0;
}


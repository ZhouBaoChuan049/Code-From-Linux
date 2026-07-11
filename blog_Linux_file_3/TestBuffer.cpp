#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>   
#include <cstring>  
void Func()
{
	close (1);
	pid_t fd = open("test.txt",O_CREAT | O_WRONLY | O_APPEND , 0666);
	printf("Hello bit %d",12323232);
	printf("Hello bit %d",12323232);
	printf("Hello bit %d",12323232);
	printf("Hello bit %d",12323232);
	printf("Hello bit %d",12323232);
	printf("Hello bit %d",12323232);
	char* msg = "11223344332";
	write(fd ,msg,strlen(msg));
	close(fd);
}
int main()
{
	Func();
	return 0;
}

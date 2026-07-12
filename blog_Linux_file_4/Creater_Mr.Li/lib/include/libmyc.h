#pragma once

#define NODE_FLUSH (1<<0)
#define LINE_FLUSH (1<<1)
#define FULL_FLUSH (1<<2)

#define MAX_SIZE 100

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
typedef struct IO_FILE
{
	int fileno ;
	int filestate ;
	char filebuf[MAX_SIZE] ;
	size_t size_filebuf ;
	int Strategy_flush;
}MyFILE;

MyFILE* Fopen(const char* file , const char* mode);

size_t Fwrite(MyFILE* file , size_t size , const char* ptr);

void Fclose(MyFILE* file);

void Fflush(MyFILE* file);













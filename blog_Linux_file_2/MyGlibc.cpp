//#pragma once
//
//#define NODE_FLUSH (1<<0)
//#define LINE_FLUSH (1<<1)
//#define FULL_FLUSH (1<<2)
//#define MAX_SIZE 100
//typedef struct IO_FILE
//{
//        int fileno ;
//        int filestate ;
//        char filebuf[MAX_SIZE] ;
//        size_t size_filebuf ;
//        int Strategy_flush;
//};MyFILE
//
//MyFILE* Fopen(const char* file , const char* mode);
//
//size_t Fwrite(MyFILE* file , size_t size , const char* ptr);
//
//int Fclose(MyFILE* file);
//
//int Fflush(MyFILE* file);
#include"MyGlibc.h"
MyFILE* BuyMyFILE(int fd ,int flag)
{
	MyFILE* f = (MyFILE*)malloc(sizeof(MyFILE));
	if(f==NULL) return NULL;
	f->fileno = fd;
	f->filestate = flag;
	f->size_filebuf = 0;
	f->Strategy_flush = LINE_FLUSH;
	memset(f->filebuf,0,MAX_SIZE);
	return f;
}

MyFILE* Fopen(const char* file , const char* mode)
{
	int fd = -1 ;
	size_t flag =-1;
	if(strcmp(mode ,"r")==0)
	{
		flag = O_CREAT | O_RDONLY;
		fd = open( file ,flag,0666 );
	}
	else if(strcmp(mode,"w")==0)
	{
		flag = O_CREAT | O_WRONLY | O_TRUNC;
		fd = open( file,flag ,0666);
	}
	else if(strcmp(mode ,"a")==0)
	{
		flag = O_CREAT | O_WRONLY | O_APPEND;
		fd = open( file ,flag ,0666);
	}
	if(fd ==-1) return NULL;
       return BuyMyFILE(fd ,flag);	

}


size_t Fwrite(MyFILE* file , size_t size , const char* ptr)
{
	memcpy(file->filebuf+file->size_filebuf,ptr,size);
	file->size_filebuf += size;
	if((file->Strategy_flush&LINE_FLUSH)&&file->filebuf[file->size_filebuf-1]=='\n')
		Fflush(file);
	return 0;
}

void Fclose(MyFILE* file)
{
	if(file->fileno<0)
		return ;
	Fflush(file);	
	close(file->fileno);
	free(file);
}

void Fflush(MyFILE* file)
{
	if(file->size_filebuf==0)
		return ;
	write(file->fileno,file-> filebuf,file->size_filebuf);
	file->size_filebuf = 0;
}


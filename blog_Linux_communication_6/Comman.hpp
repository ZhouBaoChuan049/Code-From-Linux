#pragma once
#include<iostream>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string>
#include<cstring>
#include <fcntl.h>
#include<cstdio>

#define PIPE_FILE "./fifo"

#define ERR_MEMORY(m) do{           \
    std :: string _exception = m ;  \
    throw _exception ;              \
} while(false)                      



const char* _pathname = ".";
const int object_id = 0x01 ;

const  key_t MemKey = ftok(_pathname ,object_id);

#define SERVER 1
#define CLIENT 2
#define GETUP  1
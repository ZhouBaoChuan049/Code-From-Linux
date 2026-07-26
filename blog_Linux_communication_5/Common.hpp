#ifndef __COMMON_NAMEDPIPE_
#define __COMMON_NAMEDPIPE_

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <cstdlib>
#include <string>
#include <fcntl.h>
#include <cstring>

#define PIPE_FILE "./fifo"

#define ERR_FIFO(m) do{ \
    perror(m) ;         \
    exit(EXIT_FAILURE) ;\
} while(false)          \

#endif 